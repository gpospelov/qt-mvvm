// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_VIEWITEMTYPES_H
#define MVVM_VIEWMODEL_VIEWITEMTYPES_H

#include <mvvm/viewmodel/viewitem.h>

namespace ModelView
{

namespace ViewItemTypes
{
const int empty_item_type = QStandardItem::UserType + 1;
const int label_item_type = QStandardItem::UserType + 2;
const int data_item_type = QStandardItem::UserType + 3;
} // namespace ViewItemTypes

} // namespace ModelView

#endif  // MVVM_VIEWMODEL_VIEWITEMTYPES_H
