#ifndef QUEUE_H
#define QUEUE_H

#include <Node.h>

class Queue : public QueueADT {
private:
  void operator = (const Queue&) {}      // Protect assignment
  Queue(const Queue&) {}           // Protect copy constructor
public:
    Queue ();
    void clear();
    void enqueue(Node * node);
    Node * dequeue();
    Node * frontValue() const;
    int length() const;
private:
    Node * m_base;
    int m_count;
};

#endif // QUEUE_H
