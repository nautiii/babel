/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** Opus
*/

#ifndef OPUS_HPP_
# define OPUS_HPP_

#include "opus/opus.h"

#include <stdlib.h>
#include <vector>

# define CHANNELS 2
# define FRAME_SIZE 480
# define MAX_PACKET_SIZE 3 * 1276
# define SAMPLE_RATE 48000
# define APPLICATION OPUS_APPLICATION_VOIP
# define BITRATE 64000
# define MAX_FRAME_SIZE 6*480

#include "ICompressionManager.hpp"

namespace client
{
    namespace compression
    {
        class Opus
        {
            public:
                Opus();
                ~Opus();
            public:
                void getBuffer(std::vector<u_int16_t > buffer);
                unsigned char * encoder(std::vector<u_int16_t *> buffer);
                std::vector<opus_int16 *> decoder(const unsigned char *data);

                opus_int16 *lldecoder(const unsigned char *data);
                void encoderInit(void);
            private:    
                std::vector<u_int16_t > buffer;
                OpusEncoder *enc;
                OpusDecoder *dec;
                int err;
                int size;
                opus_int16 Fs;
                opus_int16 len;  
                opus_int16 *pcm_dec;
                std::vector<opus_int16> ret_dec;
                const opus_int16 *pcm;
                unsigned char *outOpus ;
                const opus_int16 * data;
                const unsigned char * data_dec;
        };
    }
}

using namespace client::compression;

#endif /* !OPUS_HPP_ */
