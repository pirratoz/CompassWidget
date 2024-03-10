#include "Application.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    Application window;
    window.show();
    return application.exec();
}
