#ifndef NODE_H
#define NODE_H
# include <QChar>

class Node {
public:
    Node ();
<<<<<<< HEAD
    Node (char key, int frequency);
=======
    Node (char key);
    Node (QChar key);
    Node (char key, int m_height);
>>>>>>> 6ff3a3b715a0bc079abe65456336239aeb52ac83
    ~Node ();
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
    Node * m_left;
    Node * m_right;
    Node * m_next;
    char m_key;
    int m_frequency;
    int m_height;
};

#endif // NODE_H
