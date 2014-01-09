# include <QDebug>
# include <Node.h>

Node::Node() {
    m_left = 0;
    m_right = 0;
    m_frequency = 0;
    m_key = 0;
    m_next = 0;
    m_height = 0;
}

<<<<<<< HEAD
Node::Node(char key, int frequency) {
    m_left = 0;
    m_right = 0;
    m_frequency = frequency;
    m_key = key;
    m_next = 0;
    m_height = 0;
=======
Node::Node(char key) {
    this->m_left = 0;
    this->m_right = 0;
    this->m_height = 0;
    this->m_key = key;
}

Node::Node(QChar key) {
    this->m_left = 0;
    this->m_right = 0;
    this->m_height = 0;
    this->m_key = key.toLatin1();
}

Node::Node(char key, int height) {
    this->m_left = 0;
    this->m_right = 0;
    this->m_height = height;
    this->m_key = key;
>>>>>>> 6ff3a3b715a0bc079abe65456336239aeb52ac83
}

Node::~Node() {
    m_left = 0;
    m_right = 0;
    m_frequency = 0;
    m_key = 0;
    m_next = 0;
    m_height = 0;
}

void Node::setLeft(Node *left) {
    m_left = left;
}

Node * Node::left() {
    return m_left;
}

void Node::setRight(Node *right) {
    m_right = right;
}

Node * Node::right() {
    return m_right;
}

void Node::setFrequency(int freq) {
    m_frequency = freq;
}

int Node::frequency() {
    return m_frequency;
}

void Node::setKey(char key) {
    m_key = key;
}

char Node::key() {
    return m_key;
}

bool Node::isLeaf() {
    if (left() || right()) {
        return false;
    } else {
        return true;
    }

}

void Node::setNext(Node *node)
{
    m_next = node;
}

Node *Node::next()
{
    return m_next;
}

void Node::setHeight(int height) {
    int h = height - 1;
    if (left()) left()->setHeight(h);
    if (right()) right()->setHeight(h);
    m_height = height;
}

int Node::height() {
    return m_height;
}
