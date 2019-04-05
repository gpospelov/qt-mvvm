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
#include "viewitem.h"
#include "viewmodelutils.h"
#include <QDebug>

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

//! Returns true if given SessionItem role is valid for view
bool isValidItemRole(const ModelView::ViewItem* view, int item_role) {
    if (view->item_role() == item_role)
        return true;

    if (item_role == ModelView::ItemDataRole::APPEARANCE)
        return true;

    return false;
}

}

PropertyViewModel::PropertyViewModel(QObject* parent)
    : DefaultViewModel(parent)
{

}

void PropertyViewModel::onDataChange(SessionItem* item, int role)
{
    for (auto view : findViews(item)) {

        // inform corresponding LabelView and DataView
        if (isValidItemRole(view, role)) {
            auto index = indexFromItem(view);
            dataChanged(index, index, Utils::item_role_to_qt(role));
        }
    }

    if (auto group = dynamic_cast<GroupItem*>(item)) {
        qDebug() << "AAAAA" << QString::fromStdString(group->currentType());

        auto views = findStandardViews(group);
        qDebug() << "AAAAA" << views;
        for (auto view : views)
            view->removeRows(0, view->rowCount());

        if (views.size())
            iterate(group, views.at(0));


    }

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
