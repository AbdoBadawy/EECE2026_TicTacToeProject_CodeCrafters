#include "mainwindow.h"
#include "loginwindow.h"

#include <QApplication>
#include <string>
std::string username; // remove this when including login !! include it in all files like this : extern std::string username

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.startLoginWindow();
    return a.exec();
}
