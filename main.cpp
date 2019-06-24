#include <QApplication>

#include "maze/builder.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Builder b(10, 10);
    b.create();

    return a.exec();
}
