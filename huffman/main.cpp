#include <File.h>

int main(int argc, char *argv[])
{
    File * f = new File("/home/larissartemis/workspace/FileTest/", "teste.txt");
    f->split();
    return 0;
}
