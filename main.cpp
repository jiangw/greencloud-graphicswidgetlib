#include "ctestwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CTestWindow w;
    w.show();
    
    return a.exec();
}
