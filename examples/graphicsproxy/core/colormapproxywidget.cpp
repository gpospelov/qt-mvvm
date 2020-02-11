// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "colormapproxywidget.h"
#include <mvvm/plotting/colormapcanvas.h>

ColorMapProxyWidget::ColorMapProxyWidget(ModelView::ColorMapCanvas* colormap)
{
    setWidget(colormap);
}