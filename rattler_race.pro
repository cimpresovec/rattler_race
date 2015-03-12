TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

SOURCES += main.cpp \
    mainMenu.cpp \
    assetManager.cpp \
    levelScene.cpp

HEADERS += \
    gameScene.h \
    mainMenu.h \
    assetManager.h \
    levelScene.h

