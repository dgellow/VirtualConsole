QT += widgets

TARGET = VirtualEditor
TEMPLATE = app
CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
	src/main.cpp \
	src/mainwindow.cpp

HEADERS += src/mainwindow.hpp

FORMS += src/mainwindow.ui
