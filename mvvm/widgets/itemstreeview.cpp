// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "itemstreeview.h"
#include "topitemsviewmodel.h"
#include "viewmodeldelegate.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "viewmodel.h"
#include <QVBoxLayout>
#include <QTreeView>

using namespace ModelView;

ItemsTreeView::ItemsTreeView(QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView), m_delegate(std::make_unique<ViewModelDelegate>())
{
    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_treeView);
    setLayout(layout);
}

ItemsTreeView::~ItemsTreeView() = default;


void ItemsTreeView::setViewModel(std::unique_ptr<ViewModel> viewModel)
{
    m_viewModel = std::move(viewModel);
    m_treeView->setItemDelegate(m_delegate.get());
    m_treeView->setModel(m_viewModel.get());
    m_treeView->expandAll();
    set_connected(true);
}

//! Make given item selected in QTreeView.

void ItemsTreeView::setSelected(SessionItem* item)
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

void ItemsTreeView::onSelectionChanged(const QItemSelection&, const QItemSelection&)
{
    auto indexes = m_treeView->selectionModel()->selectedIndexes();
    if (indexes.size()) {
        auto item = m_viewModel->sessionItemFromIndex(indexes.at(0));
        Q_ASSERT(item);
        itemSelected(item);
    }
}

void ItemsTreeView::set_connected(bool flag)
{
    Q_ASSERT(selectionModel());

    if (flag)
        connect(selectionModel(), &QItemSelectionModel::selectionChanged,
                this, &ItemsTreeView::onSelectionChanged);
    else
        disconnect(selectionModel(), &QItemSelectionModel::selectionChanged,
                this, &ItemsTreeView::onSelectionChanged);
}

QTreeView* ItemsTreeView::treeView()
{
    return m_treeView;
}

QItemSelectionModel* ItemsTreeView::selectionModel()
{
    return m_treeView->selectionModel();
}
