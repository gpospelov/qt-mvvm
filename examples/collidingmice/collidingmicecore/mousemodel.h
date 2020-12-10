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

//! Domain object to hold mouse info.

class MouseItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_COLOR = "P_COLOR";
    static inline const std::string P_XPOS = "P_XPOS";
    static inline const std::string P_YPOS = "P_YPOS";
    static inline const std::string P_ANGLE = "P_ANGLE";
    static inline const std::string P_SPEED = "P_SPEED";

    MouseItem();
};

//! Holds collection of mice.

class MouseModel : public ModelView::SessionModel
{
public:
    MouseModel();

    void readFromFile(const QString& name);

    void writeToFile(const QString& name);

    //! Sets undo stack to given position.
    //! value=0   - first command in the stack (corresponds to the model status "in the past")
    //! value=100 - last command in the stack (corresponds to the status "now")
    void setUndoPosition(int value);

private:
    void populate_model();
};

#endif // MOUSEMODEL_H
