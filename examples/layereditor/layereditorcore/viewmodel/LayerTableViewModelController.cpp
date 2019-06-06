// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "LayerTableViewModelController.h"
#include "LayerItems.h"
#include "item_constants.h"
#include "rowstrategyinterface.h"
#include "standardchildrenstrategies.h"
#include "viewitems.h"

using namespace ModelView;

//! Custom strategy to form table rows.

class CustomLayerRowStrategy : public RowStrategyInterface
{
public:
    QList<QStandardItem*> constructRow(SessionItem* item)
    {
        QList<QStandardItem*> result;

        if (auto multilayer = dynamic_cast<MultiLayerItem*>(item)) {
            result.push_back(new ViewLabelItem(multilayer));
            result.push_back(new ViewDataItem(multilayer->getItem(MultiLayerItem::P_NREPETITIONS)));
            result.push_back(new ViewEmptyItem()); // instead of P_MATERIAL
            result.push_back(new ViewEmptyItem()); // instead of P_THICKNESS
        }

        if (auto layer = dynamic_cast<LayerItem*>(item)) {
            result.push_back(new ViewLabelItem(layer));
            result.push_back(new ViewEmptyItem()); // insted of P_NREPETITIONS
            result.push_back(new ViewDataItem(layer->getItem(LayerItem::P_MATERIAL)));
            result.push_back(new ViewDataItem(layer->getItem(LayerItem::P_THICKNESS)));
        }

        return result;
    }
    QStringList horizontalHeaderLabels() const { return QStringList(); }
};

LayerTableViewModelController::LayerTableViewModelController(AbstractViewModel* view_model)
    : AbstractViewModelController(view_model)
{
    setRowStrategy(std::make_unique<CustomLayerRowStrategy>());
    setChildrenStrategy(std::make_unique<TopItemsStrategy>());
}
