// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "propertyviewmodel.h"
#include "sessionitem.h"
#include "groupitem.h"
#include "rowconstructor.h"

using namespace ModelView;

namespace  {
std::vector<SessionItem*> item_children(SessionItem* item) {
    std::vector<SessionItem*> result;
    if (auto group = dynamic_cast<GroupItem*>(item)) {
//        result.push_back(group->currentItem());
        result = group->currentItem()->children();
    } else {
        result = item->children();
    }
    return result;
}
}

PropertyViewModel::PropertyViewModel(QObject* parent)
    : DefaultViewModel(parent)
{

}

PropertyViewModel::~PropertyViewModel() = default;

void PropertyViewModel::iterate(SessionItem* item, QStandardItem* parent)
{
    QStandardItem* origParent(parent);
    for (auto child : item_children(item)) {

        auto row = m_row_constructor->constructRow(child);
        parent->appendRow(row);

        if (row.size())
            parent = row.at(0); // labelItem

        iterate(child, parent);
        parent = origParent;
    }
}
