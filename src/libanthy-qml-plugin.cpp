#include "libanthy-qml-plugin.h"
#include "anthy.h"

#include <qqml.h>

void Anthyqml_Qml_Plugin_Anthy_Qt5Plugin::registerTypes(const char *uri)
{
    // @uri se.behold.anthy
    qmlRegisterType<Anthy>(uri, 1, 0, "Anthy");
}


