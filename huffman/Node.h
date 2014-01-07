#ifndef NODE_H
#define NODE_H

class Node {
public:
    Node ();
    Node (char key);
    Node (char key, int m_height);
    ~Node ();
    void setLeft (Node * m_left);
    Node * left();
    void setRight (Node * m_right);
    Node * right();
    void setHeight(int m_height);
    int height();
    void setKey(char m_key);
    char key();
    bool isLeaf();
private:
    Node * m_left;
    Node * m_right;
    char m_key;
    int m_height;
};

#endif // NODE_H
