// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "LayerTableModel.h"
#include "item_constants.h"
#include "sessionitem.h"
#include "LayerTableRowConstructor.h"
#include "itemutils.h"
#include <stack>

LayerTableModel::LayerTableModel(ModelView::SessionModel* model, QObject* parent)
    : ModelView::DefaultViewModel(model, parent)
{
    setRowConstructor(std::make_unique<LayerTableRowConstructor>());
}

//! Returns (possibly filtered) vector of children of given item.
//! In given case returns only material items in a container. All property items will be handled
//! via row constructor.

// FIXME repair

//std::vector<ModelView::SessionItem*>
//LayerTableModel::item_children(const ModelView::SessionItem* item) const
//{
//    // FIXME temporary hell
//    std::vector<ModelView::SessionItem*> result;
//    if (item->modelType() == Constants::MultiLayerType) {
//        for (auto it : ModelView::Utils::TopLevelItems(*item)) {
//            if (it->modelType() == Constants::LayerType) {
//                result.push_back(it);
//            } else {
//                for (auto it2 : ModelView::Utils::TopLevelItems(*it)) {
//                    if (it2->modelType() == Constants::LayerType)
//                        result.push_back(it2);
//                }

//            }

//        }
//    }
//    return result;
//}
