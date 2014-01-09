TEMPLATE = lib
TARGET = jollaanthyplugin
QT += qml quick
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = se.behold.anthy

# Input
SOURCES += \
    src/anthy.cpp \
    src/libanthy-qml-plugin.cpp

HEADERS += \
    src/anthy.h \
    src/libanthy-qml-plugin.h \
    src/libanthy-qml-plugin.h \
    src/anthy.h

OTHER_FILES = qmldir \
    rpm/libanthy-qml-plugin.spec

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += anthy
