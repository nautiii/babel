/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** AAudioManager
*/

#ifndef AAUDIOMANAGER_HPP_
#define AAUDIOMANAGER_HPP_

#include "IAudioManager.hpp"

namespace client {

    namespace audioManager {
        
        template <typename AudioType, typename StreamParameters, typename Stream>
        class AAudioManager : public IAudioManager<AudioType> {
            typedef vector<AudioType *> Type;
            
            public:
                AAudioManager(){};
                virtual ~AAudioManager() = default;
            protected:
                virtual void StopStream() = 0;
                virtual void OpenStream() = 0;
                virtual void InitInput() = 0;
                virtual void InitOutput() = 0;
                virtual void Read(AudioType *buffers) = 0;
                virtual Type Write(Type buffers) = 0;
            protected:
                StreamParameters outputParameters;
                StreamParameters inputParameters;
                Stream *stream;
                Type buffers;
                AudioType left[480];
                AudioType right[480];
        };

    }

}

#endif /* !AAUDIOMANAGER_HPP_ */
