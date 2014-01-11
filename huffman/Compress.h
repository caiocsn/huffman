#ifndef COMPRESS_H
#define COMPRESS_H
#include <Tree.h>
#include <File.h>
#include <QDebug>
#include <iostream>
#include <QByteArray>
#include <QFile>
#include <CountOccurrence.h>
#include <CreateHuffmanTree.h>
#include <QString>

class Compress
{
public:
    Compress(QString pathFile);
    ~Compress();
    bool uncompress();
    bool compress();
private:
    QString fill(QString str);
private:
    QString m_path;
    QString m_fileName;

};

#endif // COMPRESS_H
