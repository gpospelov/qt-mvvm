// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "testwidget2.h"
#include "viewitem.h"
#include "viewmodel.h"
#include <QTreeView>
#include <QVBoxLayout>

using namespace ModelView;

TestWidget2::TestWidget2(QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView), m_model(new ViewModel(this))
{
    auto layout = new QVBoxLayout;

    m_model->setColumnCount(3);
    QStandardItem* parentItem = m_model->invisibleRootItem();

    m_treeView->setModel(m_model);

    layout->addWidget(m_treeView);

    setLayout(layout);
}
