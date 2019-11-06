// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

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
