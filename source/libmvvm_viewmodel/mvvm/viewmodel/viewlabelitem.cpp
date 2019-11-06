// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#include <mvvm/viewmodel/viewlabelitem.h>
#include <mvvm/model/mvvm_types.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/viewmodel/viewitemtypes.h>

using namespace ModelView;

ViewLabelItem::ViewLabelItem(SessionItem* item) : ViewItem(item, ItemDataRole::DISPLAY)
{
    setEditable(false); // label view is always read only
}

int ViewLabelItem::type() const
{
    return ViewItemTypes::label_item_type;
}

QVariant ViewLabelItem::data(int role) const
{
    if (!m_item)
        return QStandardItem::data(role);

    // use item's display role
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return QString::fromStdString(m_item->displayName());

    return ViewItem::data(role);
}
