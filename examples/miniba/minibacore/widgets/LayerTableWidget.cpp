// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "LayerTableWidget.h"
#include "abstractviewmodel.h"
#include "CustomModelDelegate.h"
#include "viewmodels.h"
#include "sessionitem.h"
#include "LayerTableModel.h"
#include <QTreeView>
#include <QVBoxLayout>

LayerTableWidget::LayerTableWidget(QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView), m_delegate(std::make_unique<CustomModelDelegate>())
{
    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_treeView);
    setLayout(layout);

    m_treeView->setHeaderHidden(false);
    m_treeView->setItemDelegate(m_delegate.get());
    // provide one click editing
    m_treeView->setEditTriggers(QAbstractItemView::AllEditTriggers);
    m_treeView->setAlternatingRowColors(true);
}

void LayerTableWidget::setItem(ModelView::SessionItem* container)
{
    m_viewModel = Utils::CreateLayerTableModel(container->model());
    m_viewModel->setRootSessionItem(container);
    m_treeView->setModel(m_viewModel.get());
    m_treeView->expandAll();
    m_treeView->setRootIsDecorated(false);
}

LayerTableWidget::~LayerTableWidget() = default;
