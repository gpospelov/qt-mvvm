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
#include <vector>

namespace ModelView
{
class SceneAdapterInterface;
}

class RegionOfInterestItem;
class RegionOfInterestController;
class SizeHandleElement;

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

    void setActiveHandle(SizeHandleElement* element);

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);

private:
    void create_size_handle_elements();
    void update_geometry();
    SizeHandleElement* findOpposite(SizeHandleElement* element);
    std::unique_ptr<RegionOfInterestController> controller;
    std::vector<SizeHandleElement*> handles;
    SizeHandleElement* active_handle{nullptr};
};

#endif // GRAPHICSPROXY_REGIONOFINTERESTVIEW_H
