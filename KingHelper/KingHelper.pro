#-------------------------------------------------
#
# Project created by QtCreator 2014-03-12T14:15:21
#
#-------------------------------------------------

QT       += core gui sql

TARGET = KingHelper
TEMPLATE = app


SOURCES += main.cpp\
        kinghelpmain.cpp \
    kingdbmanager.cpp \
    kingcommontools.cpp \
    kingdatacache.cpp \
    kingitemwidget.cpp \
    kinglineedit.cpp \
    kingwidgetitem.cpp \
    kingsearchedit.cpp \
    kingscreencut.cpp

HEADERS  += kinghelpmain.h \
    kingdbmanager.h \
    kinghelpdef.h \
    kingcommontools.h \
    kingdatacache.h \
    kingitemwidget.h \
    kinglineedit.h \
    kingwidgetitem.h \
    kingsearchedit.h \
    kingscreencut.h

FORMS    += kinghelpmain.ui \
    kingitemwidget.ui \
    kinglineedit.ui

RESOURCES += \
    resource.qrc

OTHER_FILES +=
