#include "main_window2.hpp"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow2 mainWindow2;
    mainWindow2.show();
    return QApplication::exec();
}
