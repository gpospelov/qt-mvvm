// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef AXISITEM_H
#define AXISITEM_H

#include <mvvm/model/compounditem.h>
#include <mvvm/model/sessionmodel.h>

/*!
@class AxisItem
@brief Domain object to hold mouse info.
*/

class AxisItem : public ModelView::CompoundItem
{
public:
    static inline const std::string COLOR = "COLOR";
    static inline const std::string THICKNESS = "THICKNESS";
    static inline const std::string OFFSET_X = "OFFSET_X";
    static inline const std::string OFFSET_Y = "OFFSET_Y";
    AxisItem();
};

#endif // AXISITEM_H
