#ifndef OCCURRENCE_H
//#include <QChar>
#define OCCURRENCE_H

class Occurrence {
public:
    Occurrence (char qCharCode);
    Occurrence ();
    ~Occurrence ();
    char character();
    int count();
    void set_char(char ch);
    void set_count(int count);
private:
    char m_char;
    int m_count;
};

#endif // OCCURRENCE_H
