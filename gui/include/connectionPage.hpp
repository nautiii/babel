/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** connectionPage
*/

#ifndef CONNECTIONPAGE_HPP_
#define CONNECTIONPAGE_HPP_

#include <QObject>
#include <QPixmap>
#include <QDialog>
#include <QMessageBox>
#include "QtUserInterface.hpp"
#include <utility>
#include <QtWidgets/QtWidgets>

class ConnectionPage : public QWidget{
    Q_OBJECT
    public:
        ConnectionPage(QtUserInterface *window, QListWidget *List);
        ~ConnectionPage();
    protected:
    private slots:
        void OnSuccessReg();
        void OnFailedReg();
        void OnSuccessLog();
        void OnFailedLog();
        void pushButtonLog();
        void pushButtonRegister();
    private:
        QtUserInterface *win;
        QLineEdit *login;
        QLineEdit *password;
};


#endif /* !CONNECTIONPAGE_HPP_ */
