#include <QBitArray>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <vector>
#include <File.h>

File::File() {
    m_path = "";
    m_filename = "";
}

File::File(QString path, QString filename) {
    m_path = path;
    m_filename = filename;
}

File::~File() {
    m_path.clear();
    m_filename.clear();
}

void File:: split()
{
    int sizeMax = 4;
    QString fullpath = m_path + m_filename;

    QFile bigFile (fullpath);
    if (bigFile.exists()) {
        bigFile.open(QIODevice::ReadWrite | QIODevice::Text);
        int length = (int) bigFile.size();
        int parts = 1 + length / (sizeMax-1);
        int achunk = length/(parts-1);
        std::vector<char> buffer (achunk);

        for (int i = 0; i < parts; i++) {
            QString partialpath = m_path + QString::number(i) + m_filename;

            bigFile.read(&buffer[0], achunk);

            QFile smallFile (partialpath);
            smallFile.open(QIODevice::ReadWrite | QIODevice::Text);
            smallFile.write(&buffer[0], achunk);
            smallFile.close();

            qDebug() << partialpath;
        }
    }
}

QByteArray File::read() {
    QFile file(m_path + m_filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);
    QString string = in.readAll();
    QByteArray byteArray;
    byteArray.append(string);

    return byteArray;
}


void File::write(QByteArray byteArray, QString repTree, int garbageSize) {
    QByteArray header;
    header.resize(2);

    QString binaryGarbageSize = QString::number(garbageSize,2);
    QString binaryTreeSize = QString::number(repTree.size(),2);
    int zeros = 16 - (binaryGarbageSize.size() + binaryTreeSize.size());
    for (int i = 0; i < zeros; ++i) {
        binaryTreeSize.prepend(QString::number(0));
    }

    QString toBit = binaryGarbageSize;
    toBit.append(binaryTreeSize);

    QBitArray toByte(16);
    for(int i = 0; i < 16; ++i) {
        if (toBit.at(i) == '0')
            toByte[i]=false;
        else
            toByte[i]=true;
    }

    for (int i = 0; i < toByte.count(); ++i) {
            header[i/8] = (header.at(i/8) | ((toByte[i]?1:0)<<(i%8)));
    }

    QByteArray filename128b;
    filename128b.append(m_filename);

    header.append(filename128b);
    header.append(repTree);

    QFile file(m_path + "compactado.huff");
    qDebug() << "header " << header;
    qDebug() << "qbytearray " << byteArray;
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    file.write(header);
    file.write(byteArray);
    file.close();
}
