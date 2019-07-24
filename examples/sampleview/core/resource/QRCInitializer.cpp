#include "QRCInitializer.h"
#include <QtGlobal>

QRCInitializer* QRCInitializer::initSampleViewResources()
{
    static bool inited = false;
    if (inited)
        return nullptr;

    Q_INIT_RESOURCE(SampleView);
    inited = true;
    return nullptr;
}
