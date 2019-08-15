#include "TextMsgAssembler.h"

#include <QSharedPointer>

TextMsgAssembler::TextMsgAssembler(QObject* parent)
    : QObject(parent)
{
    clear();
}

/**
 * @brief TextMsgAssembler::storage 将数据存储至仓库m_queue
 * @param data
 * @param len
 */
void TextMsgAssembler::storage(const char* data, const int len)
{
    if( data != NULL )
    {
        for(int i=0; i<len; i++)
        {
            m_queue.enqueue(data[i]);
        }
    }
}

/**
 * @brief TextMsgAssembler::assemble 装配文本协议对象(带状态函数)
 * @return
 */
QSharedPointer<TextMessage> TextMsgAssembler::assemble()
{
    TextMessage* ret = NULL;

    bool tryMakeMessage = false;

    if( m_type == "" )
    {
        tryMakeMessage = makeTypeAndLength();
    }
    else
    {
        tryMakeMessage = true;
    }

    if( tryMakeMessage )
    {
        ret = makeMessage();
    }

    if( ret != NULL )
    {
        clear();
    }

    return QSharedPointer<TextMessage>(ret);
}

/**
 * @brief TextMsgAssembler::reset 重置状态
 */
void TextMsgAssembler::reset()
{
    clear();
    m_queue.clear();
}

void TextMsgAssembler::clear()
{
    m_type = "";
    m_length = 0;
    m_data.clear();
}

QByteArray TextMsgAssembler::fetch(const int len)
{
    QByteArray ret;

    if( len <= m_queue.length() )
    {
        for(int i=0; i<len; i++)
        {
            ret.append(m_queue.dequeue());
        }
    }

    return ret;
}

bool TextMsgAssembler::makeTypeAndLength()
{
    bool ret = (m_queue.length() >= 8);

    if( ret )
    {
        m_type = QString(fetch(4));
        m_length = QString(fetch(4)).trimmed().toInt(&ret, 16);

        if( !ret )
        {
            clear();
        }
    }

    return ret;
}

TextMessage* TextMsgAssembler::makeMessage()
{
    TextMessage* ret = NULL;

    if( m_type != "" )
    {
        // 进入此函数时, m_data可能已有部分数据
        const int needLen = m_length - m_data.length();

        const int fetchLen = (needLen <= m_queue.length()) ? needLen : m_queue.length();

        m_data.append(fetch(fetchLen));

        if( m_data.length() == m_length )
        {
            ret = new TextMessage(m_type, m_data);
        }
    }

    return ret;
}
