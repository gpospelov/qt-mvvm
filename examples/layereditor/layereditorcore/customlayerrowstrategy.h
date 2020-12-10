// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef CUSTOMLAYERROWSTRATEGY_H
#define CUSTOMLAYERROWSTRATEGY_H

#include <QStringList>
#include <layereditorcore/samplemodel.h>
#include <mvvm/interfaces/rowstrategyinterface.h>
#include <mvvm/viewmodel/standardviewitems.h>
#include <mvvm/viewmodel/viewitem.h>
#include <vector>

//! Custom strategy to form table rows for nested multilayers and layers.

class CustomLayerRowStrategy : public ModelView::RowStrategyInterface
{
public:
    QStringList horizontalHeaderLabels() const
    {
        return QStringList() << "Type"
                             << "Nr."
                             << "Material"
                             << "Thickness";
    }

    std::vector<std::unique_ptr<ModelView::ViewItem>> constructRow(ModelView::SessionItem* item)
    {
        std::vector<std::unique_ptr<ModelView::ViewItem>> result;

        // multilayer row contains its name, repetion and placeholders (instead of material and
        // thickness)
        if (auto multilayer = dynamic_cast<MultiLayerItem*>(item)) {
            result.emplace_back(std::make_unique<ModelView::ViewLabelItem>(multilayer));
            result.emplace_back(std::make_unique<ModelView::ViewDataItem>(
                multilayer->getItem(MultiLayerItem::P_NREPETITIONS)));
            result.emplace_back(
                std::make_unique<ModelView::ViewEmptyItem>()); // instead of P_MATERIAL
            result.emplace_back(
                std::make_unique<ModelView::ViewEmptyItem>()); // instead of P_THICKNESS
        }

        // layer row contains its name, placeholder for repetition, layer material and thickness
        if (auto layer = dynamic_cast<LayerItem*>(item)) {
            result.emplace_back(std::make_unique<ModelView::ViewLabelItem>(layer));
            result.emplace_back(
                std::make_unique<ModelView::ViewEmptyItem>()); // instead of P_NREPETITIONS
            result.emplace_back(
                std::make_unique<ModelView::ViewDataItem>(layer->getItem(LayerItem::P_MATERIAL)));
            result.emplace_back(
                std::make_unique<ModelView::ViewDataItem>(layer->getItem(LayerItem::P_THICKNESS)));
        }

        return result;
    }
};

#endif //  CUSTOMLAYERROWSTRATEGY_H
