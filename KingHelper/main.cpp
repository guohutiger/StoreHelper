#include <QtGui/QApplication>
#include "kinghelpmain.h"
#include <QTextCodec>
#include <QTranslator>
#include "kinghelpdef.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    QApplication a(argc, argv);
    KingHelpMain w;
    w.show();
    


    //¹ú¼Ê»¯·­Òë
    //QTranslator translator;
    //translator.load("./resource/translator/qt_zh_CN.qm");
    //a.installTranslator(&translator);
    //qRegisterMetaType<productItem>("productItem");
    return a.exec();
}
