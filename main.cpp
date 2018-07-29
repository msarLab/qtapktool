#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QStyleFactory>
#include <QStringList>
#include <QProcess>
#include <QProcessEnvironment>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QApplication::setWindowIcon(QIcon("icon.ico"));
    //a.setStyle(QStyleFactory::create("Fusion"));
    QStringList list=QProcess::systemEnvironment();
    qDebug()<<"环境变量："<<list;

    return a.exec();
}
