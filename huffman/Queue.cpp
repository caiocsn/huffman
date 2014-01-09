#include <Queue.h>
#include <QDebug>

Queue::Queue() {}

void Queue:: clear() {
    qDebug() << "clear!";
    Node * current = m_base;
    for (int i = 0; i < m_count; ++i) {
        Node * aux = current->next;
        delete current;
        current = aux;
        delete aux;
    }
    m_count = 0;
}

void Queue:: enqueue(Node * node) {
    qDebug() << "enqueue!";
    if(m_base) {
        node->setNext(m_base);
    }
    m_base = node;
    ++m_count;
}

Node * Queue:: dequeue() {
    qDebug() << "dequeue!";
    Node * aux = m_base;
    m_base = m_base->next();
    --m_count;
    return aux->value;
}

Node * Queue::frontValue()
{
    qDebug() << "frontValue!";
    return m_base->key();
}

int Queue::length() const
{
    qDebug() << "length!";
    return m_count;
}
