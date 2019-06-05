// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "MaterialTableWidget.h"
#include "abstractviewmodel.h"
#include "viewmodeldelegate.h"
#include "sessionitem.h"
#include "MaterialTableViewModel.h"
#include "CustomCellDecoration.h"
#include <QTreeView>
#include <QVBoxLayout>

MaterialTableWidget::MaterialTableWidget(QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView), m_delegate(std::make_unique<ModelView::ViewModelDelegate>())
{
    m_delegate->setCellDecoration(std::make_unique<CustomCellDecoration>());

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

void MaterialTableWidget::setItem(ModelView::SessionItem* container)
{
    m_viewModel = std::make_unique<MaterialTableViewModel>(container->model());
    m_viewModel->setRootSessionItem(container);
    m_treeView->setModel(m_viewModel.get());
    m_treeView->expandAll();
    m_treeView->setRootIsDecorated(false);
    m_treeView->resizeColumnToContents(1);
}

MaterialTableWidget::~MaterialTableWidget() = default;
