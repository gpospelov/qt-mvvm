// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/model/sessionitem.h>
#include <mvvm/viewmodel/standardviewitems.h>

using namespace ModelView;

RootViewItem::RootViewItem(SessionItem* item) : ViewItem(item, ItemDataRole::DATA) {}

//! ---------------------------------------------------------------------------

ViewLabelItem::ViewLabelItem(SessionItem* item) : ViewItem(item, ItemDataRole::DISPLAY) {}

QVariant ViewLabelItem::data(int role) const
{
    if (!item())
        return QVariant();

    // use item's display role
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return QString::fromStdString(item()->displayName());

    return ViewItem::data(role);
}

//! ---------------------------------------------------------------------------

ViewDataItem::ViewDataItem(SessionItem* item) : ViewItem(item, ItemDataRole::DATA) {}

Qt::ItemFlags ViewDataItem::flags() const
{
    Qt::ItemFlags result = ViewItem::flags();
    if (item() && item()->isEditable() && item()->isEnabled())
        result |= Qt::ItemIsEditable;
    return result;
}

ViewEmptyItem::ViewEmptyItem() : ViewItem(nullptr, 0) {}

QVariant ViewEmptyItem::data(int) const
{
    return QVariant();
}
