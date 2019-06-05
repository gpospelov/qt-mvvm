// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "MaterialTableViewModel.h"
#include "item_constants.h"
#include "sessionitem.h"
#include "MaterialTableRowConstructor.h"

MaterialTableViewModel::MaterialTableViewModel(ModelView::SessionModel* model, QObject* parent)
    : ModelView::DefaultViewModel(model, parent)
{
//    setRowConstructor(std::make_unique<MaterialTableRowConstructor>());
}

//! Returns (possibly filtered) vector of children of given item.
//! In given case returns only material items in a container. All property items will be handled
//! via row constructor.

// FIXME repair

//std::vector<ModelView::SessionItem*>
//MaterialTableModel::item_children(const ModelView::SessionItem* item) const
//{
//    std::vector<ModelView::SessionItem*> result;
//    if (item->modelType() == Constants::MaterialContainerType)
//        result = item->children();
//    return result;
//}
