# include <CountOccurrence.h>
# include <QDebug>

CountOccurrence :: CountOccurrence (QByteArray file) {
    set_file(file);
    QList<Occurrence> occurrence = QList<Occurrence>();
    set_occurrence(occurrence);
}

CountOccurrence :: ~CountOccurrence () {
}

void CountOccurrence :: count () {
    for (int i = 0; i < file().size(); i++) {
        bool exist = false;
        for (int j = 0; j < occurrence().size(); j++) {
            if(m_file[i] == m_occurrence[j].character()) {
                exist = true;
            }
        }

        if (!exist) {
            char ch = m_file.at(i);
            Occurrence occur = Occurrence(ch);
            int ct = m_file.count(ch);
            occur.set_count(ct);
            m_occurrence.append(occur);
            qDebug() << "!exist ~ ch " << ch << " ~ ct " << ct;
        }
    }
}

QList<Occurrence> CountOccurrence :: orderByOccurrence () {
    qDebug() << "\n";
    QList<Occurrence> ordered  = QList<Occurrence>();

    for (int i = 0; i < m_occurrence.size(); ++i) {
        for (int j = i; j > 0 && m_occurrence[j].count() < m_occurrence[j-1].count(); --j) {
            Occurrence aux = m_occurrence[j];
            m_occurrence[j] = m_occurrence[j-1];
            m_occurrence[j-1] = aux;
        }
    }
    for (int i = 0; i < m_occurrence.size(); ++i) {
        qDebug() << m_occurrence[i].character() << " appear " << m_occurrence[i].count();
        ordered.append(m_occurrence[i]);
    }

    return ordered;
}

void CountOccurrence :: set_file (QByteArray file) {
    m_file = file;
}

void CountOccurrence :: set_occurrence (QList<Occurrence> occurrence) {
    m_occurrence = occurrence;
}

QByteArray CountOccurrence :: file () {
    return m_file;
}

QList<Occurrence> CountOccurrence :: occurrence () {
    return m_occurrence;
}

void CountOccurrence :: print () {
    for (int i = 0; i < occurrence().size(); i++) {
        qDebug() << "Char: " << m_occurrence[i].character();
        qDebug() << "*** Occurrence: " << m_occurrence[i].count();
    }
}
