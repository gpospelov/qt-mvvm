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
#include <memory>

namespace ModelView
{
class GraphCanvas;
class SceneAdapterInterface;
} // namespace ModelView

class CustomPlotProxyWidget;
class RegionOfInterestItem;

//! Custom graphics scene to show QCustomPlot with additional elements on top.

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GraphicsScene(QObject* parent = nullptr);
    ~GraphicsScene() override;

    void setContext();
    void update_size(const QSize& newSize);
    ModelView::SceneAdapterInterface* getSceneAdapter() const;

private:
    void createPlotProxy(ModelView::GraphCanvas* plot_canvas);
    CustomPlotProxyWidget* plot_proxy{nullptr};
    std::unique_ptr<ModelView::SceneAdapterInterface> scene_adapter;
};

#endif //  GRAPHICSPROXY_GRAPHICSSCENE_H
