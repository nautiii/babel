/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** PortAudio
*/

#include "../include/PortAudio.hpp"

using namespace client::audioManager::portAudio;

PortAudio::PortAudio()  
{
    cout << "Init Portaudio" << endl;
}

PortAudio::~PortAudio()
{
    StopStream();
    this->error = Pa_Terminate();
    if (error != paNoError)
        printf("Error with PortAudio: %s\n", Pa_GetErrorText(this->error));
}

void PortAudio::InitInput()
{
    this->inputParameters.device = Pa_GetDefaultInputDevice();
    if (inputParameters.device == paNoDevice)
        printf("Error: No default input device.\n");
    inputParameters.channelCount = 2;               
    inputParameters.sampleFormat = paInt16;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;
    if (this->error != paNoError) {
        printf("%s\n", Pa_GetErrorText(this->error));
    }
}

void PortAudio::InitOutput()
{
    outputParameters.device = Pa_GetDefaultOutputDevice(); 
    if (outputParameters.device == paNoDevice)
        printf("Error: No default output device.\n");
    outputParameters.channelCount = 2;
    outputParameters.sampleFormat = paInt16;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultHighOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL; 
}

void PortAudio::OpenStream()
{
    this->error = Pa_OpenStream(&stream, &inputParameters, &outputParameters, 44100, 480, paClipOff, NULL , NULL);
    if (error != paNoError)
        printf("Error stream is not opened\n");
}

void PortAudio::start()
{
    Pa_Initialize();

    if (this->error != paNoError)
        printf("%s\n", Pa_GetErrorText(this->error));
    buffers.push_back(left);
    buffers.push_back(right);

    InitInput();
    InitOutput();
    OpenStream();
    error = Pa_StartStream(stream);
}

void PortAudio::Read(u_int16_t *buff)
{
    error = Pa_ReadStream(stream, buff, 480);
}

std::vector<u_int16_t *> PortAudio::Write(std::vector<u_int16_t *> buff)
{
    error = Pa_WriteStream(stream, buffers[0], 480);
    return (buffers);
}

void PortAudio::writeThis(u_int16_t *buff)
{
    error = Pa_WriteStream(stream, buff, 480);
}

void PortAudio::StopStream()
{
    error = Pa_StopStream(stream);
    error = Pa_CloseStream(stream);
    Pa_Terminate();
}
