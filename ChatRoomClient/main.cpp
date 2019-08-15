#include <QApplication>

#include "ChatRoomClient.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    ChatRoomClient client;
    client.show();

    return a.exec();
}
