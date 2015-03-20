TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

LIBS += -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

SOURCES += main.cpp \
    mainMenu.cpp \
    assetManager.cpp \
    levelScene.cpp \
    levelEditorScene.cpp \
    settingsScene.cpp \
    snake.cpp \
    ball.cpp

HEADERS += \
    gameScene.h \
    mainMenu.h \
    assetManager.h \
    levelScene.h \
    levelEditorScene.h \
    settingsScene.h \
    snake.h \
    ball.h

