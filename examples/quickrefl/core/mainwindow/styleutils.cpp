// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "styleutils.h"
#include <QSize>

QSize StyleUtils::ToolBarIconSize()
{
    return QSize(24, 24);
}

QSize StyleUtils::DockSizeHint()
{
    return QSize(480, 360);
}

QSize StyleUtils::DockMinimumSizeHint()
{
    return QSize(320, 240);
}
