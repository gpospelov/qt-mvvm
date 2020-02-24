// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "layerviewmodelcontroller.h"
#include "layeritems.h"
#include <mvvm/viewmodel/refviewitems.h>
#include <mvvm/viewmodel/rowstrategyinterface.h>
#include <mvvm/viewmodel/standardchildrenstrategies.h>
#include <mvvm/viewmodel/viewitems.h>
#include <mvvm/viewmodel/abstractviewmodel.h>

using namespace ModelView;

//! Custom strategy to form table rows for nested multilayers and layers.

class CustomLayerRowStrategy : public RowStrategyInterface
{
public:
    QStringList horizontalHeaderLabels() const
    {
        return QStringList() << "Name"
                             << "Nr."
                             << "Material"
                             << "Thickness";
    }

    std::vector<std::unique_ptr<RefViewItem>> constructRefRow(SessionItem* item)
    {
        std::vector<std::unique_ptr<RefViewItem>> result;

        // multilayer row contains its name, repetion and placeholders (instead of material and
        // thickness)
        if (auto multilayer = dynamic_cast<MultiLayerItem*>(item)) {
            result.emplace_back(
                std::make_unique<RefViewDataItem>(multilayer->getItem(LayerItem::P_NAME)));
            //            result.push_back(new ViewLabelItem(multilayer));
            result.emplace_back(std::make_unique<RefViewDataItem>(
                multilayer->getItem(MultiLayerItem::P_NREPETITIONS)));
            result.emplace_back(std::make_unique<RefViewEmptyItem>()); // instead of P_MATERIAL
            result.emplace_back(std::make_unique<RefViewEmptyItem>()); // instead of P_THICKNESS
        }

        // layer row contains its name, placeholder for repetition, layer material and thickness
        if (auto layer = dynamic_cast<LayerItem*>(item)) {
            result.emplace_back(
                std::make_unique<RefViewDataItem>(layer->getItem(LayerItem::P_NAME)));
            //            result.push_back(new ViewLabelItem(layer));
            result.emplace_back(std::make_unique<RefViewEmptyItem>()); // instead of P_NREPETITIONS
            result.emplace_back(
                std::make_unique<RefViewDataItem>(layer->getItem(LayerItem::P_MATERIAL)));
            result.emplace_back(
                std::make_unique<RefViewDataItem>(layer->getItem(LayerItem::P_THICKNESS)));
        }

        return result;
    }
};

LayerViewModelController::LayerViewModelController(SessionModel* model, AbstractViewModel* view_model)
    : AbstractViewModelController(model, view_model)
{
    setRowStrategy(std::make_unique<CustomLayerRowStrategy>());
    setChildrenStrategy(std::make_unique<TopItemsStrategy>());
}
