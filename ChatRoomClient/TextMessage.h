/*
 * 文本协议类
 * 文本协议对象组成: 4字节(type) + 4字节(data的length) + [0-0xFF]字节(data)
*/

#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include <QObject>

class TextMessage : public QObject
{
    Q_OBJECT

private:
    QString m_type;
    QString m_data;

public:
    explicit TextMessage(QObject* parent = NULL);
    TextMessage(const QString& type, const QString& data, QObject* parent = NULL);

    QString type() const;
    int length() const;
    QString data() const;

    QByteArray serialize() const;
    bool unSerialize(const QByteArray& byteArray);
};

#endif // TEXTMESSAGE_H
