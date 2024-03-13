#include "mainwindow.h"
#include <QApplication>
#include"Serial/Serialer.h"
#include"Kernel.h"
int main(int argc, char *argv[])
{

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    CKernel ker;

    return a.exec();
}
