# include <Node.h>

Node::Node() {
    this->m_left = 0;
    this->m_right = 0;
    this->m_frequency = 0;
    this->m_key = 0;
}

Node::Node(char key, int frequency) {
    this->m_left = 0;
    this->m_right = 0;
    this->m_frequency = frequency;
    this->m_key = key;
}

Node::~Node() {
    this->m_left = 0;
    this->m_right = 0;
    this->m_frequency = 0;
    this->m_key = 0;
}

void Node::setLeft(Node *left) {
    this->m_left = left;
}

Node * Node::left() {
    return this->m_left;
}

void Node::setRight(Node *right) {
    this->m_right = right;
}

Node * Node::right() {
    return this->m_right;
}

void Node::setFrequency(int height) {
    this->m_frequency = height;
}

int Node::frequency() {
    return this->m_frequency;
}

void Node::setKey(char key) {
    this->m_key = key;
}

char Node::key() {
    return this->m_key;
}

bool Node::isLeaf() {
    if (this->left() || this->right()) {
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
