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

class RegionOfInterestItem;

//! Graphics object to represent RegionOfInterestItem on graphics scene.

class RegionOfInterestView : public QGraphicsObject
{
    Q_OBJECT

public:
    RegionOfInterestView(RegionOfInterestItem* item);

    QRectF boundingRect() const override;

private:
    RegionOfInterestItem* item{nullptr};
    QRectF bounding_rect;
};

#endif // GRAPHICSPROXY_REGIONOFINTERESTVIEW_H
