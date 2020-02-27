// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialeditorwidget.h"
#include "materialitems.h"
#include "materialmodel.h"
#include "materialselectionmodel.h"
#include "materialtableview.h"
#include "materialtreeview.h"
#include <QVBoxLayout>
#include <mvvm/model/modelutils.h>
#include <mvvm/viewmodel/standardviewmodels.h>
#include <mvvm/viewmodel/viewmodeldelegate.h>

MaterialEditorWidget::MaterialEditorWidget(MaterialModel* material_model, QWidget* parent)
    : QWidget(parent), material_model(material_model),
      view_model(ModelView::Utils::CreatePropertyTableViewModel(material_model)),
      selection_model(new MaterialSelectionModel(view_model.get(), this)),
      material_view(new MaterialTreeView),
      m_delegate(std::make_unique<ModelView::ViewModelDelegate>())
{
    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(material_view);
    setLayout(layout);

    view_model->setRootSessionItem(
        ModelView::Utils::TopItem<MaterialContainerItem>(material_model));
    material_view->setModel(view_model.get());
    material_view->setSelectionModel(selection_model);
    material_view->setItemDelegate(m_delegate.get());
}

MaterialEditorWidget::~MaterialEditorWidget() = default;

MaterialSelectionModel* MaterialEditorWidget::selectionModel() const
{
    return selection_model;
}
