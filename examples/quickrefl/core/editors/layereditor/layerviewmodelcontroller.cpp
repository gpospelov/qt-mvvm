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
#include <mvvm/viewmodel/rowstrategyinterface.h>
#include <mvvm/viewmodel/standardchildrenstrategies.h>
#include <mvvm/viewmodel/viewitems.h>

using namespace ModelView;

//! Custom strategy to form table rows for nested multilayers and layers.

class CustomLayerRowStrategy : public RowStrategyInterface
{
public:
    QList<QStandardItem*> constructRow(SessionItem* item)
    {
        QList<QStandardItem*> result;

        // multilayer row contains its name, repetion and placeholders (instead of material and
        // thickness)
        if (auto multilayer = dynamic_cast<MultiLayerItem*>(item)) {
            result.push_back(new ViewLabelItem(multilayer));
            result.push_back(new ViewDataItem(multilayer->getItem(MultiLayerItem::P_NREPETITIONS)));
            result.push_back(new ViewEmptyItem()); // instead of P_MATERIAL
            result.push_back(new ViewEmptyItem()); // instead of P_THICKNESS
        }

        // layer row contains its name, placeholder for repetition, layer material and thickness
        if (auto layer = dynamic_cast<LayerItem*>(item)) {
            result.push_back(new ViewLabelItem(layer));
            result.push_back(new ViewEmptyItem()); // instead of P_NREPETITIONS
            result.push_back(new ViewDataItem(layer->getItem(LayerItem::P_MATERIAL)));
            result.push_back(new ViewDataItem(layer->getItem(LayerItem::P_THICKNESS)));
        }

        return result;
    }
    QStringList horizontalHeaderLabels() const
    {
        return QStringList() << "Type"
                             << "Nr."
                             << "Material"
                             << "Thickness";
    }
};

LayerViewModelController::LayerViewModelController(AbstractViewModel* view_model)
    : AbstractViewModelController(view_model)
{
    setRowStrategy(std::make_unique<CustomLayerRowStrategy>());
    setChildrenStrategy(std::make_unique<TopItemsStrategy>());
}
