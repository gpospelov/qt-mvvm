// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXY_COLORMAPPROXYWIDGET_H
#define GRAPHICSPROXY_COLORMAPPROXYWIDGET_H

#include <QGraphicsProxyWidget>

namespace ModelView
{
class ColorMapCanvas;
}

//! Custom proxy widget to embed color map in graphics scene.

class ColorMapProxyWidget : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    ColorMapProxyWidget(ModelView::ColorMapCanvas* colormap);
};

#endif //  GRAPHICSPROXY_COLORMAPPROXYWIDGET_H
