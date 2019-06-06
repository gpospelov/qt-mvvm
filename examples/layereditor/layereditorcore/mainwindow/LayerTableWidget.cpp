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
#include "sessionitem.h"
#include "LayerTableViewModel.h"
#include <QTreeView>
#include <QVBoxLayout>

using namespace ModelView;

LayerTableWidget::LayerTableWidget(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView), m_delegate(std::make_unique<CustomModelDelegate>(models))
{
    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_treeView);
    setLayout(layout);

    m_treeView->setItemDelegate(m_delegate.get());
    m_treeView->setEditTriggers(QAbstractItemView::AllEditTriggers);
}

void LayerTableWidget::setItem(ModelView::SessionItem* container)
{
    m_viewModel = std::make_unique<LayerTableViewModel>(container->model());
    m_viewModel->setRootSessionItem(container);

    m_treeView->setModel(m_viewModel.get());
}

LayerTableWidget::~LayerTableWidget() = default;
