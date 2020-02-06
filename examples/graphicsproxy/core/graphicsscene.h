// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXY_GRAPHICSSCENE_H
#define GRAPHICSPROXY_GRAPHICSSCENE_H

#include <QGraphicsScene>

namespace ModelView
{
class ColorMapCanvas;
}

class ColorMapProxyWidget;

//! Custom graphics scene to show QCustomPlot with additional elements on top.

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene(QObject* parent);

    void setColorMap(ModelView::ColorMapCanvas* colormap);

    void update_size(const QSize& newSize);

private:
    ColorMapProxyWidget* colormap_proxy{nullptr};
};

#endif //  GRAPHICSPROXY_GRAPHICSSCENE_H
