#include "TextMessage.h"

TextMessage::TextMessage(QObject* parent)
    : QObject(parent),
      m_type(""),
      m_data("")
{}

TextMessage::TextMessage(const QString& type, const QString& data, QObject* parent)
    : QObject(parent)
{
    m_type = type.trimmed();
    m_type.resize(4, ' ');

    // 考虑中文
    m_data = data.left(0xFFFF/4);
}

QString TextMessage::type() const
{
    return m_type;
}

int TextMessage::length() const
{
    return m_data.length();
}

QString TextMessage::data() const
{
    return m_data;
}

/**
 * @brief TextMessage::serilaize 将协议对象转化为UTF8编码字节流
 * @return
 */
QByteArray TextMessage::serialize() const
{
    QByteArray ret;

    QByteArray dataArray = m_data.toUtf8();

    QString len = QString::number(dataArray.length(), 16);
    len.resize(4, ' ');

    ret.append(m_type.toStdString().c_str(), 4);
    ret.append(len.toStdString().c_str(), 4);
    ret.append(dataArray);

    return ret;
}

/**
 * @brief TextMessage::unSerialize 将UTF8编码字节流转化为协议对象
 * @param byteArray
 * @return
 */
bool TextMessage::unSerialize(const QByteArray& byteArray)
{
    bool ret = (byteArray.length() >= 8);

    if( ret )
    {
        const QString type = byteArray.left(4);

        const int len = byteArray.mid(4, 4).trimmed().toInt(&ret, 16);

        ret = ret && (len == byteArray.length()-8);

        if( ret )
        {
            m_type = type;
            m_data = byteArray.mid(8);
        }
    }

    return ret;
}
