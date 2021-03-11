/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** AReceiver.hpp
*/

#ifndef ARECEIVER_HPP_
# define ARECEIVER_HPP_

#include "IReceiver.hpp"

namespace server
{
    template<typename Data, typename Size, typename Package>
    class AReceiver : IReceiver<Data, Size, Package>
    {
        public:
            virtual ~AReceiver() = default;
        public:
            virtual Package deserialize() = 0;
            virtual Data &getData() noexcept override;
            virtual const Size &getSize() const noexcept override;
        protected:
            Size _size;
            Data _data;
    };

    template<typename Data, typename Size, typename Package>
    Data &AReceiver<Data, Size, Package>::getData() noexcept
    {
        return _data;
    }

    template<typename Data, typename Size, typename Package>
    const Size &AReceiver<Data, Size, Package>::getSize() const noexcept
    {
        return _size;
    }
}

#endif /* !ARECEIVER_HPP_ */