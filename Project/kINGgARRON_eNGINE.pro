#-------------------------------------------------
#
# Project created by QtCreator 2019-02-19T11:02:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kINGgARRON_eNGINE
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    myopenglwidget.cpp \
    gcomponent.cpp \
    gobject.cpp \
    inspectorwidget.cpp \
    gtransformwidget.cpp \
    grenderwidget.cpp \
    gcomponenttransform.cpp \
    gcomponentrender.cpp \
    gscene.cpp \
    vertexformat.cpp \
    submesh.cpp \
    mesh.cpp

HEADERS += \
    mainwindow.h \
    myopenglwidget.h \
    gcomponent.h \
    gobject.h \
    inspectorwidget.h \
    gtransformwidget.h \
    grenderwidget.h \
    gcomponenttransform.h \
    gcomponentrender.h \
    gscene.h \
    vertexformat.h \
    submesh.h \
    mesh.h

FORMS += \
    mainwindow.ui \
    gtransformwidget.ui \
    grenderwidget.ui \

LIBS += -lopengl32

QT += opengl

DISTFILES += \
    shaders/shaderl_vert.vsh \
    shaders/shaderl_frag.fsh

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ThirdParty/Assimp/lib/windows/ - lassimp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ThirdParty/Assimp/lib/windows/ - lassimpd
else:unix: LIBS += -L$$PWD/../ThirdParty/Assimp/lib/osx/ - lassimp.4.1.0
INCLUDEPATH += $$PWD/../ThirdParty/Assimp/include
DEPENDPATH += $$PWD/../ThirdParty/Assimp/include
