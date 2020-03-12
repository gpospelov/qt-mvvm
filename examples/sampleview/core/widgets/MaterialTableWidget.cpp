// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "MaterialTableWidget.h"
#include "MaterialControlPanel.h"
#include "MaterialModel.h"
#include "MaterialTableView.h"
#include "MaterialItems.h"
#include <QHeaderView>
#include <QVBoxLayout>
#include <mvvm/viewmodel/defaultcelldecorator.h>
#include <mvvm/viewmodel/standardviewmodels.h>
#include <mvvm/viewmodel/viewmodeldelegate.h>
#include <mvvm/model/modelutils.h>

MaterialTableWidget::MaterialTableWidget(MaterialModel* material_model, QWidget* parent)
    : QWidget(parent), m_material_table(new QTableView),
      view_model(ModelView::Utils::CreatePropertyTableViewModel(material_model)),
      m_delegate(std::make_unique<ModelView::ViewModelDelegate>())

{
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_material_table);

    view_model->setRootSessionItem(
        ModelView::Utils::TopItem<MaterialContainerItem>(material_model));
    m_material_table->setModel(view_model.get());
    m_material_table->setItemDelegate(m_delegate.get());
}

MaterialTableWidget::~MaterialTableWidget() = default;
