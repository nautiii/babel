/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** IReceiver.hpp
*/

#ifndef IRECEIVER_HPP_
# define IRECEIVER_HPP_

namespace server
{
    template<typename Data, typename Size, typename Package>
    class IReceiver
    {
        public:
            virtual ~IReceiver() = default;
        public:
            virtual Package deserialize() = 0;
            virtual Data &getData() noexcept = 0;
            virtual const Size &getSize() const noexcept= 0;
    };
}

#endif /* !IRECEIVER_HPP_ */