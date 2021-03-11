/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** connectionPage
*/

#include "connectionPage.hpp"
#include "Protocol.hpp"

ConnectionPage::ConnectionPage(QtUserInterface *window, QListWidget *WidgetList)
{
    win = window;
    QPixmap pix("resources/pic.jpg");
    QLabel *img = new QLabel(this);
    img->setAlignment(Qt::AlignCenter);
    img->resize(1100, 1000);
    pix.scaled(QSize(1100,1000),  Qt::KeepAspectRatio);
    QVBoxLayout* layout = new QVBoxLayout(this);
    QPushButton *logButton = new QPushButton(this);
    QPushButton *regButton = new QPushButton(this);
    layout->setAlignment(Qt::AlignHCenter);
    logButton->setMaximumWidth(68);
    regButton->setMaximumWidth(68);
    int w = img->width ();
    int h = img->height ();
    img->setPixmap (pix.scaled (w,h));
    img->show();
    login = new QLineEdit(this);
    password = new QLineEdit(this);
    password->setEchoMode(QLineEdit::Password);
    login->setMaximumWidth(200);
    password->setMaximumWidth(200);
    layout->insertWidget(1, login);
    layout->insertWidget(2, password);
    layout->insertWidget(3, regButton);
    layout->insertWidget(4, logButton);
    regButton->setText("Register");
    logButton->setText("Log");
    connect(logButton, SIGNAL(clicked()), this, SLOT(pushButtonLog()));
    connect(regButton, SIGNAL(clicked()), this, SLOT(pushButtonRegister()));
    login->show();
    password->show();
    logButton->show();
    regButton->show();
}

ConnectionPage::~ConnectionPage(){
}

void ConnectionPage::pushButtonLog()
{
    QString username_input = this->login->text();
    QString password_input = this->password->text();
    QString args = username_input +  SEPARATOR + password_input;
    std::string tmp = args.toUtf8().constData();

    if (username_input.isEmpty() == true || password_input.isEmpty() == true)
        QMessageBox::information(this, "Log", "Account / Password field is empty");
    else
        win->getNetworkManager()->send(protocol::LOGIN, tmp);
    return;
}

void ConnectionPage::pushButtonRegister()
{
    QString username_input = this->login->text();
    QString password_input = this->password->text();
    QString args = username_input + SEPARATOR + password_input;
    std::string tmp = args.toUtf8().constData();
    
    if (username_input.isEmpty() == true || password_input.isEmpty() == true)
        QMessageBox::information(this, "Register", "Account / Password field is empty");
    else
        win->getNetworkManager()->send(protocol::REGISTER, tmp);
    return;
}

void ConnectionPage::OnSuccessReg() {
    QMessageBox::information(this, "Register", "Account succesfully created");
    win->changeState(page_state_t::main_page);
}

void ConnectionPage::OnFailedReg() {
    QMessageBox::information(this, "Error", "Account already exist");
}

void ConnectionPage::OnSuccessLog() {
    QMessageBox::information(this, "Login", "Account succesfully logged");
    std::vector<std::string> save = win->getTotalPayload();
    for (int i = 1; i < save.size(); i++) {
        QString text = QString::fromStdString(save[i]);
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(text);
        win->getList()->insertItem(win->getList()->count(), newItem);
        text.clear();
    }
    win->changeState(page_state_t::main_page);
}

void ConnectionPage::OnFailedLog() {
    QMessageBox::information(this, "Login", "Username and / or Password are incorrect");
}

