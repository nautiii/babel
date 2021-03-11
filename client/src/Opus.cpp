/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** Opus
*/

#include "Opus.hpp"

Opus::Opus()
{
    Fs = SAMPLE_RATE;
    pcm = new opus_int16 [FRAME_SIZE * CHANNELS *sizeof(opus_int16)];
    outOpus = new unsigned char [MAX_PACKET_SIZE];
    outOpus = (unsigned char *)data;
}

Opus::~Opus()
{

}

std::vector<opus_int16 *> Opus::decoder(const unsigned char *data)
{
    std::vector<opus_int16> left;
    std::vector<opus_int16> right;
    std::vector<opus_int16 *> data_return;

    dec = opus_decoder_create(Fs, CHANNELS, &err);
    size = opus_decoder_get_size(CHANNELS);
    err = opus_decoder_init(dec, Fs, CHANNELS);
    data_dec = data;
    auto num_sample = opus_decode(dec, data, len, pcm_dec, FRAME_SIZE, 0);

    for (int i = 0; i != 481; i++ ) {
            left[i] = pcm_dec[i];
            i++;
    }
    for (int i = 480; i != 961; i++ ) {
        right[i] = pcm_dec[i];
        i++;
    }
    data_return.push_back(left.data());
    data_return.push_back(right.data());
    return (data_return);
}

void Opus::getBuffer(std::vector<u_int16_t > buffer) 
{
    this->buffer = buffer;
}

std::vector<u_int16_t> arrayToVector(u_int16_t *data)
{ 
    std::vector<u_int16_t> vec;

    for (int i = 0; i != 481; i++) {
        vec.push_back(data[i]);
    }
    return(vec);
}

void Opus::encoderInit(void)
{
	enc = opus_encoder_create(SAMPLE_RATE, 2, OPUS_APPLICATION_VOIP, &err);
    size = opus_encoder_get_size(2);
    err = opus_encoder_init(enc, Fs, CHANNELS, APPLICATION);
}

unsigned char *Opus::encoder(std::vector<u_int16_t *> buffer) 
{
    std::vector<u_int16_t> right = arrayToVector(buffer[0]);
    std::vector<u_int16_t> left = arrayToVector(buffer[1]);

    right.insert(right.end(), left.begin(), left.end());
    len = opus_encode(enc, pcm, 480, outOpus, Fs);
    return (outOpus);
}