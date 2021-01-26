// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXYCORE_AXESRECTANGLEVIEW_H
#define GRAPHICSPROXYCORE_AXESRECTANGLEVIEW_H

#include <QGraphicsObject>

namespace ModelView {
class SceneAdapterInterface;
}

namespace GraphicsProxy {

//! Transparent rectangle to cover axes area of QCustomPlot on QGraphicsScene. The size of
//! rectangle always matches axes viewport at any zoom level. Hides all children items which
//! go out of axes range of QCustomPlot.

class AxesRectangleView : public QGraphicsObject {
    Q_OBJECT

public:
    AxesRectangleView(const ModelView::SceneAdapterInterface* scene_adapter);

    QRectF boundingRect() const override;

    void advance(int phase) override;

protected:
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

private:
    const ModelView::SceneAdapterInterface* m_sceneAdapter{nullptr};
    QRectF m_rect;
};

} // namespace GraphicsProxy

#endif // GRAPHICSPROXYCORE_AXESRECTANGLEVIEW_H
