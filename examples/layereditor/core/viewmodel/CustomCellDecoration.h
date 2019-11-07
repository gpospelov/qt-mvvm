// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef CUSTOMCELLDECORATION_H
#define CUSTOMCELLDECORATION_H

#include <mvvm/viewmodel/defaultcelldecoration.h>

class QModelIndex;

//! Generates cell decorations for MaterialEditor.
//! Current implementation just removes color name and leaves only color pixmap.

class CustomCellDecoration : public ModelView::DefaultCellDecoration
{
public:
    bool hasCustomDecoration(const QModelIndex& index) const;
    std::string cellText(const QModelIndex& index) const;
};

#endif //  CUSTOMCELLDECORATION_H
