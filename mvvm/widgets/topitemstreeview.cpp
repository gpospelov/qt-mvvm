// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "topitemstreeview.h"
#include "topitemsviewmodel.h"
#include "viewmodeldelegate.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include <QVBoxLayout>
#include <QTreeView>

using namespace ModelView;

TopItemsTreeView::TopItemsTreeView(QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView), m_delegate(std::make_unique<ViewModelDelegate>())
{
    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_treeView);
    setLayout(layout);

    m_treeView->setItemDelegate(m_delegate.get());
    set_connected(true);
}

TopItemsTreeView::~TopItemsTreeView() = default;

void TopItemsTreeView::setModel(SessionModel* model)
{
    m_viewModel = std::make_unique<TopItemsViewModel>();
    m_viewModel->setSessionModel(model);
    m_treeView->setModel(m_viewModel.get());
    m_treeView->expandAll();
}

//! Make given item selected in QTreeView.

void TopItemsTreeView::setSelected(SessionItem* item)
{
    if (!m_viewModel)
        return;

    auto indexes = m_viewModel->indexOfSessionItem(item);
    if (!indexes.empty()) {
        set_connected(false);
        selectionModel()->select(indexes.at(0), QItemSelectionModel::ClearAndSelect);
        set_connected(true);
    }
}

//! Processes selections in QTreeView. Finds SessionItem corresponding to selected indexes
//! and emit itemSelected signal.

void TopItemsTreeView::onSelectionChanged(const QItemSelection&, const QItemSelection&)
{
    auto indexes = m_treeView->selectionModel()->selectedIndexes();
    if (indexes.size()) {
        auto item = m_viewModel->sessionItemFromIndex(indexes.at(0));
        Q_ASSERT(item);
        itemSelected(item);
    }
}

void TopItemsTreeView::set_connected(bool flag)
{
    Q_ASSERT(selectionModel());

    if (flag)
        connect(selectionModel(), &QItemSelectionModel::selectionChanged,
                this, &TopItemsTreeView::onSelectionChanged);
    else
        disconnect(selectionModel(), &QItemSelectionModel::selectionChanged,
                this, &TopItemsTreeView::onSelectionChanged);
}

QTreeView* TopItemsTreeView::treeView()
{
    return m_treeView;
}

QItemSelectionModel* TopItemsTreeView::selectionModel()
{
    return m_treeView->selectionModel();
}
