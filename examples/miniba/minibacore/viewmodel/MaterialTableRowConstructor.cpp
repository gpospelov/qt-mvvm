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
#include "viewitems.h"
#include <stdexcept>

QList<QStandardItem*> MaterialTableRowConstructor::constructRow(ModelView::SessionItem* item)
{
    if (item->modelType() != Constants::SLDMaterialType)
        throw std::runtime_error("MaterialTableRowConstructor::constructRow() -> Not material item");

    QList<QStandardItem*> result;
    result.push_back(new ModelView::ViewDataItem(item->getItem(SLDMaterialItem::P_NAME)));
    result.push_back(new ModelView::ViewDataItem(item->getItem(SLDMaterialItem::P_SLD_REAL)));
    result.push_back(new ModelView::ViewDataItem(item->getItem(SLDMaterialItem::P_SLD_IMAG)));
    return result;
}

int MaterialTableRowConstructor::columnCount() const
{
    const int fixed_number_of_row_elements(3); // name, sld_real, sld_imag
    return fixed_number_of_row_elements;
}
