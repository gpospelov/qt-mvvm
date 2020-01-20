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
    static inline const std::string P_X_INI = "P_X_INI";
    static inline const std::string P_Y_INI = "P_Y_INI";
    static inline const std::string P_X_FIN = "P_X_FIN";
    static inline const std::string P_Y_FIN = "P_Y_FIN";
    SegmentItem();
};

#endif // SEGMENTITEM_H
