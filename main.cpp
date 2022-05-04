#include "converterform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConverterForm cg;
    cg.show();

    return a.exec();
}
