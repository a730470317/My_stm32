#include "pc_assistant.h"
#include <QtWidgets/QApplication>
#include <QStyleFactory> 
#include "qtextcodec.h"
#include "qfileinfo.h"

#include <functional>
#include <iostream>
#include <string>


int main(int argc, char *argv[])
{
    //解决库路径问题============info@seatrix.com
    QTextCodec *xcodec = QTextCodec::codecForLocale();
    QString exeDir = xcodec->toUnicode(QByteArray(argv[0]));
    QString BKE_CURRENT_DIR = QFileInfo(exeDir).path();
    QStringList  libpath;
    libpath << BKE_CURRENT_DIR + QString::fromLocal8Bit("/plugins/platforms");
    libpath << BKE_CURRENT_DIR << BKE_CURRENT_DIR + QString::fromLocal8Bit("/plugins/imageformats");
    libpath << BKE_CURRENT_DIR + QString::fromLocal8Bit("/plugins");
    libpath << QApplication::libraryPaths();
    QApplication::setLibraryPaths(libpath);
    //=========================
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication a(argc, argv);
   
    pc_assistant w; 
    w.show();
    return a.exec();
}
