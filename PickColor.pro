#-------------------------------------------------
#
# Project created by cfl997@163.com
#
#-------------------------------------------------

QT       += core gui
RC_FILE += icon.rc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PickColor
TEMPLATE = app

#下面的定义使编译器发出警告，如果你使用
#Qt中任何被标记为弃用的特性(确切的警告)
#取决于你的编译器)。请参阅的文件
#弃用的API，以便知道如何将代码从它移植出去。
DEFINES += QT_DEPRECATED_WARNINGS

#如果你使用了不推荐的api，你也可以让你的代码编译失败。
#为了这样做，取消下面一行的注释。
#您也可以选择禁用已弃用的api只到某个版本的Qt。
#定义+= QT_DISABLE_DEPRECATED_BEFORE=0x060000 #禁用所有在Qt 6.0.0之前弃用的api

CONFIG += c++11

SOURCES += \
        main.cpp \
        PickColor.cpp \
    MyDialog.cpp

HEADERS += \
        PickColor.h \
    MyDialog.h

FORMS += \
        PickColor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resource.qrc
