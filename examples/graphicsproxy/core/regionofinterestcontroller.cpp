// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "regionofinterestcontroller.h"
#include "regionofinterestview.h"
#include "sceneitems.h"

struct RegionOfInterestController::RegionOfInterestControllerImpl {
    RegionOfInterestView* roi_view{nullptr};
    RegionOfInterestControllerImpl(RegionOfInterestView* view) : roi_view(view) {}
};

RegionOfInterestController::RegionOfInterestController(RegionOfInterestItem* item,
                                                       RegionOfInterestView* view)
    : p_impl(std::make_unique<RegionOfInterestControllerImpl>(view))
{
    setItem(item);
}

RegionOfInterestController::~RegionOfInterestController() = default;

void RegionOfInterestController::subscribe() {}
