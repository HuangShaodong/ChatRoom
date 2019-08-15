/*
 * 文本协议装配类
*/

#ifndef TEXTMSGASSEMBLER_H
#define TEXTMSGASSEMBLER_H

#include <QObject>
#include <QQueue>

#include "TextMessage.h"

class TextMsgAssembler : public QObject
{
    Q_OBJECT

private:
    QQueue<char> m_queue;
    QString m_type;
    int m_length;
    QByteArray m_data;

    void clear();
    QByteArray fetch(const int len);
    bool makeTypeAndLength();
    TextMessage* makeMessage();

public:
    explicit TextMsgAssembler(QObject* parent = NULL);

    void storage(const char* data, const int len);
    QSharedPointer<TextMessage> assemble();
    void reset();
};

#endif // TEXTMSGASSEMBLER_H
