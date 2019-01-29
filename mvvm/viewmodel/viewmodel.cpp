// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "viewmodel.h"
#include "sessionmodel.h"
#include "itemutils.h"
#include "sessionitem.h"
#include "viewitems.h"

using namespace ModelView;

namespace {

//! Constructs row (display name and data) for given item.
QList<QStandardItem* > constructRow(SessionItem* item)
{
    QList<QStandardItem* > result;
    result.append(new ViewLabelItem(item));
    if (item->data(ItemDataRole::DATA).isValid())
        result.append(new ViewDataItem(item));
    return result;
}

}


ViewModel::ViewModel(QObject* parent)
    : QStandardItemModel(parent)
    , m_sessionModel(nullptr)
{
    setItemPrototype(new ViewEmptyItem);
}

void ViewModel::setSessionModel(SessionModel* model)
{
    m_sessionModel = model;
    update_model();
}

void ViewModel::update_model()
{
    clear();
    if(!m_sessionModel)
        return;

    setColumnCount(2);

    iterate(m_sessionModel->rootItem(), invisibleRootItem());
}

void ViewModel::iterate(SessionItem* item, QStandardItem* parent)
{
    QStandardItem* origParent(parent);
    for (auto child : item->children()) {
        auto row = constructRow(child);
        if (row.size()) {
            parent->appendRow(row);
            parent = row.at(0); // labelItem
        }
        iterate(child, parent);
        parent = origParent;
    }
}
