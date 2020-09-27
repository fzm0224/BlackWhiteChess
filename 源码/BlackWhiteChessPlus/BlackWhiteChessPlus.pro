#-------------------------------------------------
#
# Project created by QtCreator 2018-05-21T16:26:08
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BlackWhiteChessPlus
TEMPLATE = app


SOURCES += main.cpp\
        startui.cpp \
    chessboard.cpp \
    chessai.cpp \
    about.cpp \
    ask.cpp

HEADERS  += startui.h \
    chessboard.h \
    chessai.h \
    about.h \
    ask.h

RESOURCES += \
    image.qrc

DISTFILES += \
    icon.rc

RC_FILE=icon.rc
