// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "MaterialTableRowConstructor.h"
#include "item_constants.h"
#include "sessionitem.h"
#include "MaterialItems.h"
#include "viewdataitem.h"
#include "viewitems.h"
#include <stdexcept>

QList<QStandardItem*> MaterialTableRowConstructor::constructRow(ModelView::SessionItem* item)
{
    if (item->modelType() != Constants::SLDMaterialType)
        throw std::runtime_error("MaterialTableRowConstructor::constructRow() -> Not material item");

    QList<QStandardItem*> result;
    result.push_back(new ModelView::ViewDataItem(item->getItem(SLDMaterialItem::P_NAME)));
    result.push_back(new ModelView::ViewDataItem(item->getItem(SLDMaterialItem::P_COLOR)));
    result.push_back(new ModelView::ViewDataItem(item->getItem(SLDMaterialItem::P_SLD_REAL)));
    result.push_back(new ModelView::ViewDataItem(item->getItem(SLDMaterialItem::P_SLD_IMAG)));
    return result;
}

QStringList MaterialTableRowConstructor::horizontalHeaderLabels() const
{
    return QStringList() << "Name" << "#" << "SLD, real" << "SLD, imag";
}
