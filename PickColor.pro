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

#����Ķ���ʹ�������������棬�����ʹ��
#Qt���κα����Ϊ���õ�����(ȷ�еľ���)
#ȡ������ı�����)������ĵ��ļ�
#���õ�API���Ա�֪����ν����������ֲ��ȥ��
DEFINES += QT_DEPRECATED_WARNINGS

#�����ʹ���˲��Ƽ���api����Ҳ��������Ĵ������ʧ�ܡ�
#Ϊ����������ȡ������һ�е�ע�͡�
#��Ҳ����ѡ����������õ�apiֻ��ĳ���汾��Qt��
#����+= QT_DISABLE_DEPRECATED_BEFORE=0x060000 #����������Qt 6.0.0֮ǰ���õ�api

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
