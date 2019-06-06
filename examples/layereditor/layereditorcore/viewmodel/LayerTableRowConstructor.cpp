// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "LayerTableRowConstructor.h"
#include "item_constants.h"
#include "sessionitem.h"
#include "LayerItems.h"
#include "viewitems.h"
#include "viewdataitem.h"
#include <stdexcept>

QList<QStandardItem*> LayerTableRowConstructor::constructRow(ModelView::SessionItem* item)
{
    if (item->modelType() != Constants::LayerType)
        throw std::runtime_error("LayerTableRowConstructor::constructRow() -> Not layer item '"+item->modelType()+"'");

    QList<QStandardItem*> result;
    result.push_back(new ModelView::ViewDataItem(item->parent()->getItem(MultiLayerItem::P_NREPETITIONS)));
    result.push_back(new ModelView::ViewDataItem(item->getItem(LayerItem::P_NAME)));
    result.push_back(new ModelView::ViewDataItem(item->getItem(LayerItem::P_MATERIAL)));
    result.push_back(new ModelView::ViewDataItem(item->getItem(LayerItem::P_THICKNESS)));
    return result;
}

QStringList LayerTableRowConstructor::horizontalHeaderLabels() const
{
    return QStringList() << "Nr." << "Name" << "Material" << "Thickness";
}
