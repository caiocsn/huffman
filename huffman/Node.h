#ifndef NODE_H
#define NODE_H
# include <QChar>

class Node {
public:
    Node ();
    Node (char key, int frequency);
    Node (char key);
    Node (QChar key);
    ~Node ();
    void setRoot (Node * root);
    Node * root();
    void setLeft (Node * left);
    Node * left();
    void setRight (Node * right);
    Node * right();
    void setFrequency(int frequency);
    int frequency();
    void setKey(char key);
    char key();
    bool isLeaf();
    void setNext(Node * node);
    Node * next();
    void setHeight(int height);
    int height();
private:
    Node * m_root;
    Node * m_left;
    Node * m_right;
    Node * m_next;
    char m_key;
    int m_frequency;
    int m_height;
};

#endif // NODE_H
