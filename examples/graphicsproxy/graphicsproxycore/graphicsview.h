// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXYCORE_GRAPHICSVIEW_H
#define GRAPHICSPROXYCORE_GRAPHICSVIEW_H

#include <QGraphicsView>

namespace GraphicsProxy {

class GraphicsScene;

//! Custom graphics view to show QCustomPlot with additional elements on top.

class GraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    GraphicsView(GraphicsScene* scene, QWidget* parent);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    GraphicsScene* m_scene{nullptr};
};

} // namespace GraphicsProxy

#endif // GRAPHICSPROXYCORE_GRAPHICSVIEW_H
