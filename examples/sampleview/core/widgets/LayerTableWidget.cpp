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

namespace {
std::unique_ptr<LayerTableViewModel> createSampleViewModel(SampleModel* model);
QTreeView* createSampleView(AbstractViewModel* model, QAbstractItemDelegate* delegate);
}

LayerTableWidget::LayerTableWidget(ApplicationModels* models, QWidget* parent)
    : QWidget(parent)
    , m_view_model(createSampleViewModel(models ? models->sampleModel() : nullptr))
    , m_delegate(std::make_unique<CustomModelDelegate>(models))
    , m_tree_view(createSampleView(m_view_model.get(), m_delegate.get()))
{
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_tree_view);
}

LayerTableWidget::~LayerTableWidget() = default;

namespace {
std::unique_ptr<LayerTableViewModel> createSampleViewModel(SampleModel* model)
{
    auto result = std::make_unique<LayerTableViewModel>(model);
    auto root = Utils::TopItem<MultiLayerItem>(model);
    result->setRootSessionItem(root);
    return result;
}

QTreeView* createSampleView(AbstractViewModel* model, QAbstractItemDelegate* delegate)
{
    std::unique_ptr<QTreeView> result(new QTreeView);
    result->setModel(model);
    result->setItemDelegate(delegate);

    result->setAlternatingRowColors(true);
    result->expandAll();
    result->header()->setSectionResizeMode(QHeaderView::Stretch);

    return result.release();
}
}
