#-------------------------------------------------
#
# Project created by QtCreator 2020-03-25T10:56:55
#
#-------------------------------------------------

QT       += sql widgets core gui serialport



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BankSimulPaaIkkuna
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        paaikkuna.cpp

HEADERS += \
        paaikkuna.h \
    connection.h \

FORMS += \
        paaikkuna.ui

# INCLUDEPATH +=


LIBS += C:\BankSimul\build-BankSimulPaaIkkuna-Desktop_Qt_5_12_1_MinGW_64_bit-Release\release\DLLTiliTapahtumat.dll
LIBS += C:\BankSimul\build-BankSimulPaaIkkuna-Desktop_Qt_5_12_1_MinGW_64_bit-Release\release\DLLKortinLuku.dll
LIBS += C:\BankSimul\build-BankSimulPaaIkkuna-Desktop_Qt_5_12_1_MinGW_64_bit-Release\release\Kate.dll
LIBS += C:\BankSimul\build-BankSimulPaaIkkuna-Desktop_Qt_5_12_1_MinGW_64_bit-Release\release\Siirto.dll
LIBS += C:\BankSimul\build-BankSimulPaaIkkuna-Desktop_Qt_5_12_1_MinGW_64_bit-Release\release\NostaRahaaLIB.dll
LIBS += C:\BankSimul\build-BankSimulPaaIkkuna-Desktop_Qt_5_12_1_MinGW_64_bit-Release\release\MaksaLasku_DLL.dll


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
