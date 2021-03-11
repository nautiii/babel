/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** ICompressionManager.hpp
*/

#ifndef ICOMPRESSIONMANAGER_HPP_
# define ICOMPRESSIONMANAGER_HPP_

namespace client
{
    namespace compression
    {
        template<typename Buffer, typename Data, typename DecodedBuffer>
        class ICompressionManager
        {
            public:
                virtual ~ICompressionManager() = default;
            public:
                virtual Data encoder(Buffer buf) = 0;
                virtual DecodedBuffer decoder(const Data data) = 0;
        };
    }
}

#endif /* !ICOMPRESSIONMANAGER_HPP_ */