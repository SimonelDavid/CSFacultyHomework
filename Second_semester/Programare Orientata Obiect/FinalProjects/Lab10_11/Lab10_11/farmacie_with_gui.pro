QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    entity.cpp \
    errors.cpp \
    generator.cpp \
    main.cpp \
    application.cpp \
    repository.cpp \
    service.cpp \
    undo.cpp \
    validator.cpp

HEADERS += \
    application.h \
    entity.h \
    errors.h \
    generator.h \
    repository.h \
    service.h \
    undo.h \
    validator.h

FORMS += \
    application.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
