QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spatial_mapping
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
    camera.cpp \
    glwidget.cpp \
    geometryengine.cpp \
    camerawidget.cpp \
    spatialmapping.cpp

HEADERS += \
    camera.h \
    glwidget.h \
    geometryengine.h \
    camerawidget.h \
    spatialmapping.h

INCLUDEPATH += /home/ubuntu/JetPack/64_TX1/Linux_for_Tegra/rootfs/usr/local/zed/include \
               /home/ubuntu/JetPack/64_TX1/Linux_for_Tegra/rootfs/usr/local/cuda/include

LIBS += -L/home/ubuntu/JetPack/64_TX1/Linux_for_Tegra/rootfs/usr/local/zed/lib \
            -lsl_input \
            -lsl_core \
            -lsl_zed \
        -L/home/ubuntu/JetPack/64_TX1/Linux_for_Tegra/rootfs/usr/local/cuda/lib64 \
            -lnppial \
            -lnppisu \
            -lnppicc \
            -lnppicom \
            -lnppidei \
            -lnppif \
            -lnppig \
            -lnppim \
            -lnppist \
            -lnppitc \
            -lnpps \
            -lnppc

target.path = /home/nvidia/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    fshader.glsl \
    vshader.glsl

RESOURCES += \
    shaders.qrc
