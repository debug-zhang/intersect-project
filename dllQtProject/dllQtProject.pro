QT -= gui

TEMPLATE = lib
DEFINES += DLLQTPROJECT_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/core/IOHandler.cpp \
    ../src/core/container.cpp \
    ../src/core/dot.cpp \
    ../src/core/line.cpp \
    ../src/core/pch.cpp \
    ../src/core/radial.cpp \
    ../src/core/segment.cpp \
    dllqtproject.cpp

HEADERS += \
    ../src/core/IOHandler.h \
    ../src/core/container.h \
    ../src/core/dot.h \
    ../src/core/exception.h \
    ../src/core/framework.h \
    ../src/core/graph.h \
    ../src/core/line.h \
    ../src/core/pch.h \
    ../src/core/radial.h \
    ../src/core/segment.h \
    dllQtProject_global.h \
    dllqtproject.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
