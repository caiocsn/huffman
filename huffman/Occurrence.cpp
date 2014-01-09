# include <Occurrence.h>

Occurrence::Occurrence(char charCode) {
    set_char(charCode);
    set_count(0);
    setNext(0);
}

Occurrence::Occurrence() {}

Occurrence::~Occurrence() {}

char Occurrence::character() {
    return m_char;
}

int Occurrence::count() {
    return m_count;
}

void Occurrence::set_char(char ch) {
    m_char = ch;
}

void Occurrence::set_count(int count) {
    m_count = count;
}

Occurrence Occurrence::m_next() {
    return m_next;
}

void Occurrence::setNext(Occurrence * next) {
    m_next = next;
}
