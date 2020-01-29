// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "layereditorwidget.h"
#include "applicationmodels.h"
#include "customeditorfactory.h"
#include "layeritems.h"
#include "layerselectionmodel.h"
#include "layertreeview.h"
#include "layerviewmodel.h"
#include "materialmodel.h"
#include "samplemodel.h"
#include <QVBoxLayout>
#include <mvvm/model/modelutils.h>
#include <mvvm/viewmodel/abstractviewmodel.h>
#include <mvvm/viewmodel/standardviewmodels.h>
#include <mvvm/viewmodel/viewmodeldelegate.h>

LayerEditorWidget::LayerEditorWidget(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), view_model(std::make_unique<LayerViewModel>(models->sampleModel())),
      selection_model(new LayerSelectionModel(view_model.get(), this)),
      layer_view(new LayerTreeView), m_delegate(std::make_unique<ModelView::ViewModelDelegate>())
{
    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(layer_view);
    setLayout(layout);

    m_delegate->setEditorFactory(std::make_unique<CustomEditorFactory>(models));
    view_model->setRootSessionItem(
        ModelView::Utils::TopItem<MultiLayerItem>(models->sampleModel()));

    layer_view->setModel(view_model.get());
    layer_view->setSelectionModel(selection_model);
    layer_view->setItemDelegate(m_delegate.get());
}

LayerEditorWidget::~LayerEditorWidget() = default;

LayerSelectionModel* LayerEditorWidget::selectionModel() const
{
    return selection_model;
}
