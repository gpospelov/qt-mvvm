// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include <mvvm/viewmodel/viewdataitem.h>
#include <mvvm/model/customvariants.h>
#include <mvvm/viewmodel/viewitemtypes.h>
#include <mvvm/model/mvvm_types.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/viewmodel/viewmodelutils.h>

using namespace ModelView;

ViewDataItem::ViewDataItem(SessionItem* item) : ViewItem(item, ItemDataRole::DATA)
{
    // SessionItem::isEnabled means simply gray color and read only.
    setEditable(item->isEditable() && item->isEnabled());

    // QStandardItem::isEnabled means something completely different (no interactions).
    // We leave it by default.
}

int ViewDataItem::type() const
{
    return ViewItemTypes::data_item_type;
}

QVariant ViewDataItem::data(int role) const
{
    if (!m_item)
        return QStandardItem::data(role);

    if (role == Qt::CheckStateRole)
        return Utils::CheckStateRole(*m_item);

    else if (role == Qt::DecorationRole)
        return Utils::DecorationRole(*m_item);

    return ViewItem::data(role);
}
