#ifndef CHATROOMCLIENT_H
#define CHATROOMCLIENT_H

#include <QWidget>

class ChatRoomClient : public QWidget
{
    Q_OBJECT

public:
    ChatRoomClient(QWidget* parent = NULL);
    ~ChatRoomClient();
};

#endif // CHATROOMCLIENT_H
