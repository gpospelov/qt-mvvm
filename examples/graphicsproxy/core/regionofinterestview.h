// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXY_REGIONOFINTERESTVIEW_H
#define GRAPHICSPROXY_REGIONOFINTERESTVIEW_H

#include <QGraphicsObject>

namespace ModelView
{
class SceneAdapterInterface;
}

class RegionOfInterestItem;

//! Graphics object to represent RegionOfInterestItem on graphics scene.
//! Follows standard QGraphicsScene notations: (x,y) origin is top left corner.

class RegionOfInterestView : public QGraphicsObject
{
    Q_OBJECT

public:
    RegionOfInterestView(RegionOfInterestItem* item,
                         const ModelView::SceneAdapterInterface* scene_adapter);

    QRectF boundingRect() const override;

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);

private:
    void update_geometry();
    qreal width() const;
    qreal height() const;
    qreal left() const;
    qreal right() const;
    qreal top() const;
    qreal bottom() const;

    double par(const std::string& name) const;

    RegionOfInterestItem* item{nullptr};
    QRectF rect;
    const ModelView::SceneAdapterInterface* scene_adapter{nullptr};
};

#endif // GRAPHICSPROXY_REGIONOFINTERESTVIEW_H
