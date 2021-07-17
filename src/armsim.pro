#-------------------------------------------------
#
# Project created by QtCreator 2018-09-03T16:16:48
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = armsim
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
QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    main.cpp \
    loader.cpp \
    options.cpp \
    memory.cpp \
    log.cpp \
    testram.cpp \
    testloader.cpp \
    cpu.cpp \
    computer.cpp \
    worker.cpp \
    testcomputer.cpp \
    testcpu.cpp \
    instruction.cpp \
    dataprocessinginstruction.cpp \
    loadstoreinstruction.cpp \
    getinstructioninstance.cpp \
    mov.cpp \
    testinstructions.cpp \
    add.cpp \
    mvn.cpp \
    sub.cpp \
    rsb.cpp \
    mul.cpp \
    and.cpp \
    orr.cpp \
    eor.cpp \
    bic.cpp \
    str.cpp \
    ldr.cpp \
    ldm.cpp \
    stm.cpp \
    swi.cpp \
    cmp.cpp \
    b.cpp \
    bx.cpp \
    mrs.cpp \
    notify.cpp \
    msr.cpp \
    keypress.cpp \
    uxth.cpp \
    uxtb.cpp \
    uxtah.cpp \
    uxtab.cpp \
    uhadd.cpp \
    uhaddsubx.cpp \
    uhsub.cpp \
    uhsubaddx.cpp


FORMS += \
        loader.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    armsim.pro

DISTFILES += \
    armsim.pro.user

HEADERS += \
    loader.h \
    options.h \
    include/elf.h \
    include/CLI11.hpp \
    log.h \
    testram.h \
    testloader.h \
    memory.h \
    cpu.h \
    computer.h \
    worker.h \
    testcomputer.h \
    testcpu.h \
    instruction.h \
    dataprocessinginstruction.h \
    loadstoreinstruction.h \
    getinstructioninstance.h \
    mov.h \
    testinstructions.h \
    add.h \
    mvn.h \
    sub.h \
    rsb.h \
    mul.h \
    and.h \
    orr.h \
    eor.h \
    bic.h \
    str.h \
    ldr.h \
    ldm.h \
    stm.h \
    swi.h \
    cmp.h \
    b.h \
    bx.h \
    mrs.h \
    notify.h \
    msr.h \
    keypress.h \
    uxth.h \
    uxtb.h \
    uxtah.h \
    uxtab.h \
    uhadd.h \
    uhaddsubx.h \
    uhsub.h \
    uhsubaddx.h

INCLUDEPATH += $$PWD/include/

QT += testlib
CONFIG += qt console warn_on depend_includepath testcase

RESOURCES += \
    resources.qrc
