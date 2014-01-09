/*
public static Node makeHuffmanTree(int frequencies[], String text[]) {
        PriorityQueue<Node> queue = new PriorityQueue<Node>();
        for (int i = 0; i < text.length; i++) {
            Node n = new Node(text[i], frequencies[i]);
            queue.add(n);
        }
        Node root = null;
        while (queue.size() > 1)  {
            Node least1 = queue.poll();
            Node least2 = queue.poll();
            Node combined = new Node(least1.frequency + least2.frequency);
            combined.right = least1;
            combined.left = least2;
            least1.parent = combined;
            least2.parent = combined;
            queue.add(combined);
            // Keep track until we actually find the root
            root = combined;
        }
        return root;
    }
*/

#include <Tree.h>
#include <File.h>
#include <QDebug>
#include <iostream>
#include <QByteArray>
#include <QFile>
#include <CountOccurrence.h>

int main() {
    Node * root = new Node();
    Node * l = new Node('L', 1);
    Node * a = new Node('A', 2);
    Node * r = new Node('R', 1);
    Node * i = new Node('I', 1);
    Node * s = new Node('S', 2);
    Node * v1 = new Node();
    Node * v2 = new Node();
    Node * v3 = new Node();

    Tree * t = new Tree(root);
    root->setRight(v1);
    v1->setRight(s);
    v1->setLeft(a);
    root->setLeft(v2);
    v2->setRight(v3);
    v2->setLeft(l);
    v3->setRight(r);
    v3->setLeft(i);

    t->createRep();

    File * f = new File("/home/larissartemis/workspace/huffman/huffman/", "teste.txt");
    QByteArray q = f->read();
    f->write(q, t->rep(), 5);
    qDebug() << "done";

    return 0;
}
