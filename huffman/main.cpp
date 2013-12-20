#include <File.h>
#include <QDebug>
#include <QByteArray>

int main(int argc, char *argv[])
{
    File * f = new File("/home/larissartemis/workspace/FileTest/", "teste.txt");
    // f->split();

    QByteArray q = f->read();
    QString s;
    s.append(q);

    f->write(q);

    qDebug() << "done";
    return 0;
}
