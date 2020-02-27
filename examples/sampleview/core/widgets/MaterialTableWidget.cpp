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
#include <mvvm/viewmodel/defaultcelldecorator.h>
#include <QHeaderView>
#include <QVBoxLayout>

MaterialTableWidget::MaterialTableWidget(MaterialModel* material_model, QWidget* parent)
    : QWidget(parent),
      m_material_table(new QTableView)
{
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_material_table);
}

MaterialTableWidget::~MaterialTableWidget() = default;

