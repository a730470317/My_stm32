#include "pc_assistant.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pc_assistant w;
    w.show();
    return a.exec();
}
