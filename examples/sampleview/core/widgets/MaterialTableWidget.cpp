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
#include "MaterialTableViewModel.h"
#include "MaterialViewDelegate.h"
#include <mvvm/viewmodel/defaultcelldecoration.h>
#include <QHeaderView>
#include <QVBoxLayout>

namespace
{
std::unique_ptr<QStyledItemDelegate>
createMaterialTableDelegate(MaterialViewController& view_controller);

QTableView* createMaterialTable(MaterialViewController& view_controller,
                                QStyledItemDelegate* delegate);
} // namespace

MaterialTableWidget::MaterialTableWidget(MaterialModel* material_model, QWidget* parent)
    : QWidget(parent), m_controller(material_model),
      m_delegate(createMaterialTableDelegate(m_controller)),
      m_material_table(createMaterialTable(m_controller, m_delegate.get()))
{
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(new MaterialControlPanel(m_controller));
    layout->addWidget(m_material_table);
}

MaterialTableWidget::~MaterialTableWidget() = default;

namespace
{
std::unique_ptr<QStyledItemDelegate>
createMaterialTableDelegate(MaterialViewController& view_controller)
{
    auto result = std::make_unique<MaterialViewDelegate>(view_controller);
    result->setCellDecorator(std::make_unique<ModelView::DefaultCellDecoration>());
    return std::move(result); // complain on C++11 defect
}

QTableView* createMaterialTable(MaterialViewController& view_controller,
                                QStyledItemDelegate* delegate)
{
    std::unique_ptr<MaterialTableView> result(new MaterialTableView);
    result->setModel(&view_controller.viewModel());
    result->setSelectionModel(&view_controller.selectionModel());
    result->setItemDelegate(delegate);

    result->setAlternatingRowColors(true);
    result->verticalHeader()->hide();
    result->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    result->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    return result.release();
}
} // namespace
