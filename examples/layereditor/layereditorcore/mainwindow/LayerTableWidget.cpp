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
#include <QTableView>
#include <QVBoxLayout>

LayerTableWidget::LayerTableWidget(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_view(new QTableView), m_delegate(std::make_unique<CustomModelDelegate>(models))
{
    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_view);
    setLayout(layout);

    m_view->setItemDelegate(m_delegate.get());
    m_view->setEditTriggers(QAbstractItemView::AllEditTriggers);
}

void LayerTableWidget::setItem(ModelView::SessionItem* container)
{
    m_viewModel = std::make_unique<LayerTableViewModel>(container->model());
    m_viewModel->setRootSessionItem(container);
    m_view->setModel(m_viewModel.get());
    m_view->setSpan(1, 0, 2, 1); // fake span without connection with real MultiLayer
}

LayerTableWidget::~LayerTableWidget() = default;
