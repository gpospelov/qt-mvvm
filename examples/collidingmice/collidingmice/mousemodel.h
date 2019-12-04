// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MOUSEMODEL_H
#define MOUSEMODEL_H

#include <mvvm/model/compounditem.h>
#include <mvvm/model/sessionmodel.h>

/*!
@class MouseItem
@brief Domain object to hold mouse info.
*/

class MouseItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_COLOR = "P_COLOR";
    static inline const std::string P_XPOS = "P_XPOS";
    static inline const std::string P_YPOS = "P_YPOS";

    MouseItem();
};

/*!
@class MouseModel
@brief Holds collection of mice.
*/

class MouseModel : public ModelView::SessionModel
{
public:
    MouseModel();

private:
    void populate_model();
};

#endif // MOUSEMODEL_H
