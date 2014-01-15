#include <Compress.h>

int main() {
    Compress d = Compress("/home/larissartemis/workspace/huffman/huffman/abacaxi.txt");
    // Compress d = Compress("/home/larissartemis/workspace/huffman/huffman/gnome-terminal.png");
    // Compress d = Compress("/home/larissartemis/workspace/huffman/huffman/artigos.csv");
    d.compress();

    Compress c = Compress("/home/larissartemis/workspace/huffman/huffman/compactado.huff");
    c.uncompress();

    qDebug() << "done";

    return 0;
}
