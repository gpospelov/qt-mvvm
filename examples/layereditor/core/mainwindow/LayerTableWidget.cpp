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
#include "ApplicationModels.h"
#include "sessionitem.h"
#include "LayerTableViewModel.h"
#include "SampleModel.h"
#include "modelutils.h"
#include "LayerItems.h"
#include <QTreeView>
#include <QVBoxLayout>
#include <QHeaderView>

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
    m_treeView->setEditTriggers(QAbstractItemView::AllEditTriggers); // provide one click editing
    m_treeView->setAlternatingRowColors(true);

    setItem(Utils::TopItem<MultiLayerItem>(models->sampleModel()));
}

void LayerTableWidget::setItem(ModelView::SessionItem* multilayer)
{
    if (!multilayer)
        return;

    m_viewModel = std::make_unique<LayerTableViewModel>(multilayer->model());
    m_viewModel->setRootSessionItem(multilayer);

    m_treeView->setModel(m_viewModel.get());
    m_treeView->expandAll();
    m_treeView->header()->setSectionResizeMode(QHeaderView::Stretch);
}

LayerTableWidget::~LayerTableWidget() = default;
