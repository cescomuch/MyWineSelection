#-------------------------------------------------
#
# Project created by QtCreator 2019-03-25T14:55:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyWineSelection
TEMPLATE = app


DEFINES += QT_DEPRECATED_WARNINGS


QMAKE_CXXFLAGS += -std=c++11


SOURCES += \
    main.cpp \
    vino.cpp \
    vinolistitem.cpp \
    vinolistwidget.cpp \
    controller.cpp \
    menu.cpp \
    model.cpp \
    inserisci.cpp \
    ricerca.cpp \
    catalogo.cpp \
    dettagliovino.cpp \
    mycomboboxtipo.cpp \
    utils.cpp

HEADERS += \
    vino.h \
    myexception.h \
    container.h \
    vinolistitem.h \
    vinolistwidget.h \
    controller.h \
    menu.h \
    model.h \
    inserisci.h \
    ricerca.h \
    catalogo.h \
    dettagliovino.h \
    mycomboboxtipo.h \
    utils.h

DISTFILES+= \
    Immagini/aromatizzato1.jpg \
    Immagini/aromatizzato2.jpg \
    Immagini/aromatizzato3.jpg \
    Immagini/barricato1.jpg \
    Immagini/barricato2.jpg \
    Immagini/barricato3.jpg \
    Immagini/liquoroso1.jpg \
    Immagini/liquoroso2.jpg \
    Immagini/liquoroso3.jpg \
    Immagini/frizzante1.jpg \
    Immagini/frizzante2.jpg \
    Immagini/frizzante3.jpg \
    Immagini/spumante1.jpg \
    Immagini/spumante2.jpg \
    Immagini/spumante3.jpg \




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
