# include <Node.h>


Node::Node(char key) {
    this->m_left = 0;
    this->m_right = 0;
    this->m_height = 0;
    this->m_key = key;
}

Node::Node(char key, int height) {
    this->m_left = 0;
    this->m_right = 0;
    this->m_height = height;
    this->m_key = key;
}

Node::~Node() {
    this->m_left = 0;
    this->m_right = 0;
    this->m_height = 0;
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

void Node::setHeight(int height) {
    this->m_height = height;
}

int Node::height() {
    return this->m_height;
}

void Node::setKey(char key) {
    this->m_key = key;
}

char Node::key() {
    return this->m_key;
}

bool Node::isLeaf() {
    return this->left() && this->right();
}
