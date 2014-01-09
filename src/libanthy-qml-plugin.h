#ifndef ANTHYQML_QML_PLUGIN_ANTHY_QT5_PLUGIN_H
#define ANTHYQML_QML_PLUGIN_ANTHY_QT5_PLUGIN_H

#include <QQmlExtensionPlugin>

class Anthyqml_Qml_Plugin_Anthy_Qt5Plugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // ANTHYQML_QML_PLUGIN_ANTHY_QT5_PLUGIN_H

