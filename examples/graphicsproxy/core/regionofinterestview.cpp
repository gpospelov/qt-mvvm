// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "regionofinterestview.h"

RegionOfInterestView::RegionOfInterestView(RegionOfInterestItem* item)
    : item(item)
{

}

QRectF RegionOfInterestView::boundingRect() const
{
    return bounding_rect;
}
