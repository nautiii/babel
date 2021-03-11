/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** IAudioManager
*/

#ifndef IAUDIOMANAGER_HPP_
#define IAUDIOMANAGER_HPP_

#include <iostream>
#include <vector>

using namespace std;

namespace client {

    namespace audioManager {

        template <typename AudioType>
        class IAudioManager {
            typedef vector<AudioType *> Type;

            public:
                virtual ~IAudioManager() = default;

                virtual void OpenStream() = 0;
                virtual void StopStream() = 0;

                virtual void InitInput() = 0;
                virtual void InitOutput() = 0;

                virtual void Read(AudioType *buffers) = 0;
                virtual Type Write(Type buffers) = 0;

        };

    }

}

#endif /* !IAUDIOMANAGER_HPP_ */
