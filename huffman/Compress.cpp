#include "Compress.h"
#include <QVariant>
#include <QBitArray>

Compress::Compress(QString pathFile) {
    m_path = pathFile;
    m_fileName = pathFile;
    for (int i = pathFile.size() -1; i >= 0; --i) {
        if (pathFile.at(i) == '/') {
            m_path.remove(i, pathFile.size()-i);
            m_path.append("/");
            m_fileName.remove(0,i+1);
            break;
        }
    }
    qDebug() << m_path;
    qDebug() << m_fileName;
}

Compress::~Compress() {
}

bool Compress::uncompress() {
    qDebug() << "unc";
    File * f = new File(m_path, m_fileName);
    QByteArray qba = f->read();
    QByteArray size;
    size.append(qba.at(0));
    size.append(qba.at(1));

    QByteArray nameFile;
    for (int i = 2; i < 130; ++i) {
        if (qba[i] == '#') {
            break;
        }
        nameFile.append(qba.at(i));
    }

    QBitArray bits(16);
    // Convert from QByteArray to QBitArray
    for(int i = 0; i < 2; ++i) {
        for(int b = 0; b < 8; ++b) {
            bits.setBit(i*8+b, size.at(i)&(1<<b));
        }
    }
    qDebug() << "bits " << bits;

    QString q;
    for (int i = 0; i < 3; ++i) {
        if (bits.at(i)) {
            q.append("1");
        } else {
            q.append("0");
        }
    }

    bool ok;
    int garbageSize = q.toInt(&ok, 2);

    QString t;
    for (int i = 3; i < 16; ++i) {
        if (bits.at(i)) {
            t.append("1");
        } else {
            t.append("0");
        }
    }
    int treeSize = t.toInt(&ok, 2);

    qDebug() << "g" << garbageSize << "t" << treeSize;

    QByteArray tree;
    qDebug() << qba.size();
    for (int i = 130; i < treeSize+130; ++i) {
        if (qba.at(i)) {
            tree.append(qba.at(i));
        }
    }

    qDebug() << "Tree: " << tree;

    Tree * t = new Tree(tree);

    // convert all data to QBitArray 'toDecode'
    // for (int i = 0; i < toDecode.size(); ++i
    //   traverse the tree; when bit is 0, go to the left; when bit is 1, go to the right
    //   if node is a leaf, get its key and append to QString 'decoded'
    // write in file with the original name

    return true;
}

bool Compress::compress() {
    File * f = new File(m_path, m_fileName);
    QByteArray qba = f->read();
    // if (qba != 0) return false;
    CountOccurrence * co = new CountOccurrence(qba);
    co->count();
    QList<Occurrence> occur = co->orderByOccurrence();
    CreateHuffmanTree * cht = new CreateHuffmanTree(occur);
    Tree * tree = cht->createTree();
    cht->createHash(tree);

    QString data;
    for (int i = 0; i < qba.size(); ++i) {
        QString pathNode = cht->hash()->value(qba.at(i));
        data.append(pathNode);
    }
    int garbageSize = 7 - data.size()%8;
    for (int i = 0; i <= garbageSize; ++i) {
        data.append("0");
    }

    QString toBit = data;
    QBitArray toByte;
    toByte.resize(data.size());
    for (int i = 0; i < data.size(); ++i) {
        if (toBit.at(i) == '0') {
            toByte[i] = true;
        }
        else {
            toByte[i] = false;
        }
    }

    QByteArray encoded;
    encoded.resize(data.size()/8);
    for (int i = 0; i < toByte.size(); ++i) {
        encoded[i/8] = (encoded.at(i/8) | ((toByte[i]?1:0)<<(i%8)));
    }

    f->write(encoded, tree->rep(), garbageSize);
    qDebug() << m_fileName << " compressed";

    return true;
}


