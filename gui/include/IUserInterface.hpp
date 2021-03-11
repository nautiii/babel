/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** IUserInterface
*/

#ifndef IUSERINTERFACE_HPP_
#define IUSERINTERFACE_HPP_

typedef enum page_state {
    connection_page,
    main_page,
    call_page,
    login_page,
} page_state_t;

class IUserInterface {
    public:
        virtual ~IUserInterface() = default;

        virtual void changeState(page_state_t newState) = 0;
        virtual void login() = 0;
        virtual void logout() = 0;
};

#endif /* !IUSERINTERFACE_HPP_ */
