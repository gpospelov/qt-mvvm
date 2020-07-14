// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QHeaderView>
#include <QTreeView>
#include <QVBoxLayout>
#include <layereditorcore/model/applicationmodels.h>
#include <layereditorcore/model/layeritems.h>
#include <layereditorcore/model/samplemodel.h>
#include <layereditorcore/viewmodel/customlayerrowstrategy.h>
#include <layereditorcore/viewmodel/custommodeldelegate.h>
#include <layereditorcore/widgets/layertablewidget.h>
#include <mvvm/factories/viewmodelfactory.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/viewmodel/standardchildrenstrategies.h>
#include <mvvm/viewmodel/viewmodel.h>

using namespace ModelView;

LayerTableWidget::LayerTableWidget(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView),
      m_delegate(std::make_unique<CustomModelDelegate>(models))
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

    m_viewModel =
        Factory::CreateViewModel<TopItemsStrategy, CustomLayerRowStrategy>(multilayer->model());
    m_viewModel->setRootSessionItem(multilayer);

    m_treeView->setModel(m_viewModel.get());
    m_treeView->expandAll();
    m_treeView->header()->setSectionResizeMode(QHeaderView::Stretch);
}

LayerTableWidget::~LayerTableWidget() = default;
