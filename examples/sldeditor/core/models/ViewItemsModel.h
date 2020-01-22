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
#include "SegmentItem.h"

namespace ModelView
{
class ExternalProperty;
}

/*!
@class ViewItemsModel
@brief This holds the model for all the graphical elements of the sld editor
*/

class ViewItemsModel : public ModelView::SessionModel
{
public:
    ViewItemsModel();

    //! Add a handle item
    HandleItem* addHandle();
    //! Add a segment item
    SegmentItem* addSegment();
     
private:

};

#endif //  VIEWITEMSMODEL_H
