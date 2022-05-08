QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game.cpp \
    game_object.cpp \
    main.cpp \
    mainwindow.cpp \
    pacman.cpp \
    pacmanTwo.cpp

HEADERS += \
    game.h \
    gameobject.h \
    mainwindow.h

FORMS += \
    mainwindow.ui


DISTFILES += \
    assets/dot.png \
    assets/dotb.png \
    assets/gate.png \
    assets/map.txt \
    assets/power_ball.png \
    assets/wall.png
    assets/download.png

RESOURCES += \
#    ../../Qt-pac-man/resources.qrc \
    assets.qrc

