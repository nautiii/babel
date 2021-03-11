/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** mainPage
*/

#include "mainPage.hpp"

MainPage::MainPage(QtUserInterface *window, QListWidget *WidgetList)
    : s(0), r(8081)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QPushButton *addButton = new QPushButton(this);
    QPushButton *deleteButton = new QPushButton(this);
    QPushButton *callButton = new QPushButton(this);
    QPushButton *friendListButton = new QPushButton(this);

    win = window;
    initFriendList = false;
    listTrigger = false;
    setFixedSize(1080, 720);
    layout->setAlignment(Qt::AlignHCenter);
    adder = new QLineEdit(this);
    friendListButton->setText(tr("Friend List"));
    friendListButton->setMaximumWidth(68);
    callButton->setText(tr("Call"));
    callButton->move(470, 310);
    callButton->setMaximumWidth(200);
    addButton->setText(tr("+"));
    addButton->move(470, 310);
    addButton->setMaximumWidth(200);
    deleteButton->setText(tr("-"));
    deleteButton->move(560, 310);
    deleteButton->show();
    deleteButton->setMaximumWidth(200);
    adder->setMaximumWidth(200);
    addButton->show();
    friendListButton->show();
    adder->show();
    deleteButton->show();
    layout->insertWidget(0, addButton);
    layout->insertWidget(1, deleteButton);
    layout->insertWidget(2, adder);
    layout->insertWidget(3, callButton);
    connect(addButton, SIGNAL(clicked()), this, SLOT(pushButtonAddFriend()));
    connect(callButton, SIGNAL(clicked()), this, SLOT(OnFriendDoubleClicked()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(pushButtonDeleteFriend()));
    connect(friendListButton, SIGNAL(clicked()), this, SLOT(pushButtonFriendList()));
}

MainPage::~MainPage()
{
}

void MainPage::pushButtonFriendList()
{
    if (listTrigger == false)
    {
        listTrigger = true;
        this->win->getList()->show();
    }
    else
    {
        listTrigger = false;
        this->win->getList()->hide();
    }
    return;
}

void MainPage::pushButtonAddFriend()
{
    QString friendInput = this->adder->text();
    std::string tmp = this->adder->text().toUtf8().constData();
    toAdd = this->adder->text().toUtf8().constData();

    if (friendInput.isEmpty() == true)
        QMessageBox::information(this, "Friend Request", "Field is empty");
    else
    {
        win->getNetworkManager()->send(protocol::FRIEND, tmp);
        QMessageBox::information(this, "Friend Request", "Friend Request issued!");
    }
    return;
}

void MainPage::pushButtonDeleteFriend()
{
    QString friendInput = this->adder->text();
    std::string tmp = this->adder->text().toUtf8().constData();
    toDelete = this->adder->text().toUtf8().constData();

    if (friendInput.isEmpty() == true)
        QMessageBox::information(this, "Friend Deletion", "Field is empty");
    else
    {
        win->getNetworkManager()->send(protocol::DELETE, tmp);
        this->toDelete = string(tmp);
        QMessageBox::information(this, "Friend Deletion", "Friend Deletion issued!");
    }
    return;
}

void MainPage::pushButtonCallFriend()
{
    return;
}

void MainPage::OnFailedFriendRequest()
{
    QMessageBox::information(this, "Friend Request", "Friend Request Failed");
}

void MainPage::OnSuccessFriendRequest()
{
    return;
}

void MainPage::OnFriendDoubleClicked()
{
    QMessageBox requestBox;
    win->setVOIPsocket(new QTcpSocket);
    win->getVOIPsocket()->bind();
    QString friendInput = this->adder->text();
    QString port = QString::number(win->getVOIPsocket()->localPort());
    QString question = "Do you want to call " + friendInput + " ?";

    requestBox.setText(question);
    requestBox.setWindowTitle("Call request");

    requestBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);

    if (requestBox.exec() == QMessageBox::Yes && friendInput.isEmpty() == false)
    {
        QString result = friendInput + ':' + port;
        win->getNetworkManager()->send(protocol::Request::CALL, result.toUtf8().constData());
    }
    else
        return;
}

void MainPage::OnSuccessFriendDeletion()
{
    int i = 0;

    if (this->toDelete.empty() == false)
    {
        QMessageBox::information(this, "Friend Deletion", "Friend Deletion successful");
        for (; i < friendList.size(); i++)
            if (this->toDelete.compare(friendList[i]) == 0)
                ;
        friendList.erase(friendList.begin() + i);
        this->toDelete.clear();
    }
    return;
}

void MainPage::OnFailedFriendDeletion()
{
    return;
}

void MainPage::OnFailedLogOutRequest()
{
    return;
}

void MainPage::OnSuccessLogOutRequest()
{
    return;
}

void MainPage::OnReceiveFriendRequest()
{
    QMessageBox requestBox;
    QString yes = ":yes";
    QString no = ":no";
    QString result = QString::fromStdString(win->getcurrentPayload());
    QString question = "Would you accept " + QString::fromStdString(win->getcurrentPayload()) + "'s friend request?";

    requestBox.setWindowTitle("Friend Request");
    requestBox.setText(question);
    requestBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    QString text = QString::fromStdString(win->getcurrentPayload());
    if (requestBox.exec() == QMessageBox::Yes)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(text);
        win->getList()->insertItem(win->getList()->count(), newItem);
        result = result + yes;
        win->getNetworkManager()->send(protocol::Request::FACCEPT, result.toUtf8().constData());
    }
    else
    {
        result = result + no;
        win->getNetworkManager()->send(protocol::Request::FACCEPT, result.toUtf8().constData());
    }
    return;
}

void MainPage::OnFriendAcceptedRequest()
{
    QString result = QString::fromStdString(win->getcurrentPayload());
    QMessageBox::information(this, "Friend request", "Friend request accepted");
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(QString::fromStdString(toAdd));
    win->getList()->insertItem(win->getList()->count(), newItem);
}

void MainPage::OnSuccessAcceptFriendRequest()
{
    QMessageBox::information(this, "Friend request", "Worked");

    return;
}

void MainPage::OnFailedAcceptFriendRequest()
{
    QMessageBox::information(this, "Friend request", "Friend accept request failed");

    return;
}

void MainPage::OnSuccessCallRequest()
{
    QMessageBox::information(this, "Call success", "Calling...");

    return;
}

void MainPage::OnFailedCallRequest()
{
    QMessageBox::information(this, "Call error", "Call initiation failed");

    return;
}

void MainPage::OnCallAcceptRequest()
{
    QMessageBox requestBox;
    QString result = QString::fromStdString(win->getcurrentPayload());

    requestBox.setText("Would you accept" + QString::fromStdString(win->getcurrentPayload()) + "'s call?");
    requestBox.setWindowTitle("Call request");
    requestBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);

    if (requestBox.exec() == QMessageBox::Yes) {
        result = result + ":yes";
        win->getNetworkManager()->send(protocol::Request::CACCEPT, result.toUtf8().constData());
        {
            std::vector<u_int16_t *> buff;
            string addr("86.246.181.227");

            s.audio.start();
            r.audio.start();
            while (true) {
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
                auto x = s.audio.Write(buff);
                s.send(/*win->getTotalPayload()[2]*/addr, 8081, x);
                s.audio.Read(x[0]);
                r.readyRead();
            }
        }
    } else {
        result = result + ":no";
        win->getNetworkManager()->send(protocol::Request::CACCEPT, result.toUtf8().constData());
    }

    return;
}

void MainPage::OnCallAcceptedRequest()
{
    {
        std::vector<u_int16_t *> buff;
        string addr("89.88.190.39");

        s.audio.start();
        r.audio.start();
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            auto x = s.audio.Write(buff);
            s.send(/*win->getTotalPayload()[2]*/addr, 8081, x);
            s.audio.Read(x[0]);
            r.readyRead();
        }
    }
    QMessageBox::information(this, "Call request", "Call request accepted");

    return;
}

void MainPage::OnSuccessCallAcceptRequest()
{
    QMessageBox::information(this, "Call accept request", "Call accept request successed");

    return;
}

void MainPage::OnFailedCallAcceptRequest()
{
    QMessageBox::information(this, "Call accept request", "Call accept request failed");
    return;
}

void MainPage::OnSuccessDeleteRequest()
{
    QMessageBox::information(this, "Delete request", "Delete request successed");
    if (this->toDelete.empty() == false)
    {
        for (int i = 0; i < win->getList()->count(); i++)
            if (QString::compare(win->getList()->item(i)->text(), QString::fromStdString(toDelete)) == 0)
                delete win->getList()->takeItem(i);
        this->toDelete.clear();
    }
    return;
}

void MainPage::OnFailedDeleteRequest()
{
    QMessageBox::information(this, "Delete request", "Delete request failed");

    return;
}
// void MainPage::OnAcceptedFriendRequest()
// {
//     return;
// }

// void MainPage::OnRefusedFriendRequest()
// {
//     //win->getClient()->send(protocol::FRIEN, tmp);

// }

// QListWidgetItem *newItem = new QListWidgetItem;
// QString text = QString::fromStdString(toAdd);
// newItem->setText(text);
// List->insertItem(List->count(), newItem);
