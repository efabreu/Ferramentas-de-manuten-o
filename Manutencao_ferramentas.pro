QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BotaoIsabella.cpp \
    addf.cpp \
    criarfolga.cpp \
    ferias.cpp \
    janela_dia.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    BotaoIsabella.h \
    addf.h \
    criarfolga.h \
    ferias.h \
    janela_dia.h \
    mainwindow.h

FORMS += \
    addf.ui \
    criarfolga.ui \
    ferias.ui \
    janela_dia.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    arquivo_recursos.qrc
