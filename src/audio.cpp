#include "audio.h"

AudioInput::AudioInput()
    : m_stream(nullptr) {
    Pa_Initialize();
    m_inputBuffer = static_cast<double*>(fftw_malloc(sizeof(double) * 1024));
    m_outputBuffer = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * (1024 / 2 + 1)));
    m_fftPlan = fftw_plan_dft_r2c_1d(1024, m_inputBuffer, m_outputBuffer, FFTW_ESTIMATE);
    m_magnitudes.resize(1024 / 2 + 1);
}

AudioInput::~AudioInput() {
    Pa_StopStream(m_stream);
    Pa_CloseStream(m_stream);
    Pa_Terminate();
    fftw_destroy_plan(m_fftPlan);
    fftw_free(m_inputBuffer);
    fftw_free(m_outputBuffer);
}

void AudioInput::startCapture() {
    Pa_OpenDefaultStream(&m_stream, 1, 0, paFloat32, 44100, 1024, audioCallback, this);
    Pa_StartStream(m_stream);
}

float AudioInput::getPrimaryFrequency() {
    float maxMagnitude = 0.0f;
    int maxIndex = 0;

    for (size_t i = 0; i < m_magnitudes.size(); ++i) {
        if (m_magnitudes[i] > maxMagnitude) {
            maxMagnitude = m_magnitudes[i];
            maxIndex = i;
        }
    }

    return 44100.0f * maxIndex / 1024;
}

int AudioInput::audioCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData) {
    AudioInput* audioInput = static_cast<AudioInput*>(userData);
    audioInput->processAudio(static_cast<const float*>(inputBuffer), framesPerBuffer);
    return paContinue;
}

void AudioInput::processAudio(const float* input, unsigned long frameCount) {
    for (unsigned long i = 0; i < frameCount; ++i) {
        m_inputBuffer[i] = input[i];
    }

    fftw_execute(m_fftPlan);

    for (size_t i = 0; i < m_magnitudes.size(); ++i) {
        m_magnitudes[i] = std::sqrt(m_outputBuffer[i][0] * m_outputBuffer[i][0] + m_outputBuffer[i][1] * m_outputBuffer[i][1]);
    }
}

