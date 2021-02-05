// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/widgets/itemstreeview.h"
#include "mvvm/viewmodel/viewmodel.h"
#include "mvvm/viewmodel/viewmodeldelegate.h"
#include <QTreeView>
#include <QVBoxLayout>

using namespace ModelView;

ItemsTreeView::ItemsTreeView(QWidget* parent)
    : QWidget(parent)
    , m_treeView(new QTreeView)
    , m_delegate(std::make_unique<ViewModelDelegate>())
    , m_block_selection(false)
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
    m_treeView->resizeColumnToContents(0);
    set_connected(true);
}

void ItemsTreeView::setViewModelDelegate(std::unique_ptr<ViewModelDelegate> delegate)
{
    m_delegate = std::move(delegate);
}

//! Make given item selected in QTreeView.

void ItemsTreeView::setSelected(SessionItem* item)
{
    // Provide possibility to clear selection when item == nullptr. Provide unit tests.
    // Make sure it works when SessionModel is already destroyed.
    if (!m_viewModel || !item)
        return;

    auto indexes = m_viewModel->indexOfSessionItem(item);
    if (!indexes.empty())
        selectionModel()->select(indexes.at(0), QItemSelectionModel::SelectCurrent);
}

void ItemsTreeView::setRootSessionItem(SessionItem* item)
{
    m_viewModel->setRootSessionItem(item);
    m_treeView->expandAll();
}

ViewModel* ItemsTreeView::viewModel() const
{
    return m_viewModel.get();
}

//! Processes selections in QTreeView. Finds SessionItem corresponding to selected indexes
//! and emit itemSelected signal.

void ItemsTreeView::onSelectionChanged(const QItemSelection&, const QItemSelection&)
{
    if (m_block_selection)
        return;

    auto indexes = m_treeView->selectionModel()->selectedIndexes();
    if (!indexes.empty()) {
        auto item = m_viewModel->sessionItemFromIndex(indexes.at(0));
        m_block_selection = true;
        emit itemSelected(item);
        m_block_selection = false;
    }
}

void ItemsTreeView::set_connected(bool flag)
{
    if (flag)
        connect(selectionModel(), &QItemSelectionModel::selectionChanged, this,
                &ItemsTreeView::onSelectionChanged);
    else
        disconnect(selectionModel(), &QItemSelectionModel::selectionChanged, this,
                   &ItemsTreeView::onSelectionChanged);
}

QTreeView* ItemsTreeView::treeView()
{
    return m_treeView;
}

QItemSelectionModel* ItemsTreeView::selectionModel()
{
    return m_treeView->selectionModel();
}
