#-------------------------------------------------
#
# Project created by QtCreator 2013-12-19T19:12:47
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = huffman
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Node.cpp \
    Tree.cpp \
    Occurrence.cpp \
    CountOccurence.cpp \
    NodeOccurrence.cpp \
    File.cpp

HEADERS += \
    Node.h \
    Tree.h \
    File.h \
    CountOccurrence.h \
    Occurrence.h \
    NodeOccurrence.h \
    File.h
