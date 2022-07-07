#include <iostream>
#include <QApplication>
#include <QTranslator>
#include "dames.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    if(translator.load(QLocale::system(), "Annotations", "_", a.applicationDirPath(), ".qm")) {
        a.installTranslator(&translator);
    }

    Dames d;
    d.show();

    return a.exec();
}
