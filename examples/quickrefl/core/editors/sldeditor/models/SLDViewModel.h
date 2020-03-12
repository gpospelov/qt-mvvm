// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef VIEWITEMSMODEL_H
#define VIEWITEMSMODEL_H

#include <mvvm/model/sessionmodel.h>
#include <vector>

#include "HandleItem.h"
#include "RegionOfInterestItem.h"
#include "RoughnessViewItem.h"
#include "SegmentItem.h"

namespace ModelView
{
class ExternalProperty;
}

/*!
@class ViewItemsModel
@brief This holds the model for all the graphical elements of the sld editor
*/

class SLDViewModel : public ModelView::SessionModel
{
public:
    SLDViewModel();

    //! Add a handle item
    HandleItem* addHandle();
    //! Add a segment item
    SegmentItem* addSegment(std::string layer_identifier_in);
    //! Add a roughness item
    RoughnessViewItem* addRoughness(std::string layer_identifier_in);
};

#endif //  VIEWITEMSMODEL_H
