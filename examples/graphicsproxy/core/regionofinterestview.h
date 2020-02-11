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

#include <QGraphicsItem>
#include <memory>

namespace ModelView
{
class SceneAdapterInterface;
}

class RegionOfInterestItem;
class RegionOfInterestController;

//! Graphics object to represent RegionOfInterestItem on graphics scene.
//! Follows standard QGraphicsScene notations: (x,y) origin is top left corner.

class RegionOfInterestView : public QGraphicsItem
{
public:
    RegionOfInterestView(RegionOfInterestItem* item,
                         const ModelView::SceneAdapterInterface* scene_adapter);
    ~RegionOfInterestView() override;

    QRectF boundingRect() const override;

    void advance(int phase) override;

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void update_geometry();
    std::unique_ptr<RegionOfInterestController> controller;
};

#endif // GRAPHICSPROXY_REGIONOFINTERESTVIEW_H
