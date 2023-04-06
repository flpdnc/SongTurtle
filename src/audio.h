#ifndef AUDIO_H
#define AUDIO_H

#include <portaudio.h>
#include <fftw3.h>
#include <vector>
#include <cmath>

class AudioInput {
public:
    AudioInput();
    ~AudioInput();

    void startCapture();
    float getPrimaryFrequency();

private:
    static int audioCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData);
    void processAudio(const float* input, unsigned long frameCount);

    PaStream* m_stream;
    fftw_plan m_fftPlan;
    double* m_inputBuffer;
    fftw_complex* m_outputBuffer;
    std::vector<float> m_magnitudes;
};

#endif // AUDIO_H

