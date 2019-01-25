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
#include <QDebug>

using namespace ModelView;

ViewModel::ViewModel(QObject* parent)
    : QStandardItemModel(parent)
    , m_sessionModel(nullptr)
{

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

    iterate(m_sessionModel->rootItem(), invisibleRootItem());
}

void ViewModel::iterate(SessionItem* item, QStandardItem* parent)
{
    qDebug() << "XXX" << QString::fromStdString(item->modelType()) << item->childrenCount();
    for (auto child : item->children()) {
        qDebug() << " child:" << QString::fromStdString(child->modelType());
        ViewLabelItem* labelItem = new ViewLabelItem(child);
        ViewDataItem* dataItem = new ViewDataItem(child);

        QList<QStandardItem* > row;
        row.append(labelItem);
        row.append(dataItem);

        parent->appendRow(row);
        parent = labelItem;
        iterate(child, parent);
    }
}
