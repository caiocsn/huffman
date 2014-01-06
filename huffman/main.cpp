
#include <QDebug>
#include <QByteArray>
#include <QFile>
#include <CountOccurrence.h>

int main(int argc, char *argv[])
{

    QFile *f = new QFile("/home/marilia/Downloads/teste.jpg");
    QByteArray q = f->readAll();
    CountOccurrence * counter = new CountOccurrence(q);
    counter->count();
    counter->print();
    QList<Occurrence> occurrencesOrdered = counter->orderByOccurrence();
    //qDebug() << s;
    qDebug() << "done";
    return 0;
}
