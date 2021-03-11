/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** PortAudio
*/

#ifndef PORTAUDIO_HPP_
#define PORTAUDIO_HPP_

#include "portaudio.h"
#include <iostream>
#include "AAudioManager.hpp"
#include <vector>
#include <thread>
#include <chrono>
class AAudioManager;
typedef float SAMPLE;

namespace client {

    namespace audioManager {

        namespace portAudio {

            class PortAudio : public AAudioManager<u_int16_t, PaStreamParameters, PaStream> {
                public:
                    PortAudio();
                    ~PortAudio();           
                    void OpenStream() override;
                    void StopStream() override;
                    void InitInput() override;
                    void InitOutput() override;
                    void start();
                    void Read(u_int16_t *buffers) override;
                    std::vector<u_int16_t *> Write(std::vector<u_int16_t *> buffers) override;
                    void writeThis(u_int16_t *buff);
                private:
                    PaError error;
            };

        }

    }

}

#endif /* !PORTAUDIO_HPP_ */

