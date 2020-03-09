// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SEGMENTITEM_H
#define SEGMENTITEM_H

#include <mvvm/model/compounditem.h>
#include <mvvm/model/sessionmodel.h>

/*!
@class SegmentItem
@brief Domain object to hold mouse info.
*/

class SegmentItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_COLOR = "P_COLOR";
    static inline const std::string P_X_POS = "P_X_POS";
    static inline const std::string P_Y_POS = "P_Y_POS";
    static inline const std::string P_HEIGHT = "P_HEIGHT";
    static inline const std::string P_WIDTH = "P_WIDTH";
    static inline const std::string P_HORIZONTAL = "P_HORIZONTAL";
    SegmentItem();
};

#endif // SEGMENTITEM_H
