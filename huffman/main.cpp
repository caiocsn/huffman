#include <Compress.h>

int main() {
    Compress d = Compress("/home/larissartemis/workspace/huffman/huffman/abacaxi.txt");
    d.compress();

    Compress c = Compress("/home/larissartemis/workspace/huffman/huffman/compactado.huff");
    c.uncompress();

    qDebug() << "done";

    return 0;
}
