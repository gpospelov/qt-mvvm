// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "modeleditorwidget.h"
#include "samplemodel.h"
#include <QBoxLayout>
#include <QHeaderView>
#include <QTableView>
#include <QTreeView>
#include <mvvm/viewmodel/defaultviewmodel.h>
#include <mvvm/viewmodel/propertytableviewmodel.h>
#include <mvvm/viewmodel/viewmodeldelegate.h>

using namespace ModelView;

namespace CellEditors
{

ModelEditorWidget::ModelEditorWidget(SampleModel* model, QWidget* parent)
    : QWidget(parent)
    , m_verticalTree(new QTreeView)
    , m_horizontalTree(new QTreeView)
    , m_tableView(new QTableView)
    , m_delegate(std::make_unique<ViewModelDelegate>())
{
    auto mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(10);

    mainLayout->addLayout(create_left_layout(), 1);
    mainLayout->addLayout(create_right_layout(), 3);

    setLayout(mainLayout);
    setModel(model);
}

void ModelEditorWidget::setModel(SampleModel* model)
{
    if (!model)
        return;

    // setting up left tree
    m_verticalViewModel = std::make_unique<DefaultViewModel>(model);
    m_verticalTree->setModel(m_verticalViewModel.get());
    m_verticalTree->setItemDelegate(m_delegate.get());
    m_verticalTree->expandAll();
    m_verticalTree->resizeColumnToContents(0);

    // setting up right tree
    m_horizontalViewModel = std::make_unique<PropertyTableViewModel>(model);
    m_horizontalTree->setModel(m_horizontalViewModel.get());
    m_horizontalTree->setItemDelegate(m_delegate.get());
    m_horizontalTree->expandAll();
    m_horizontalTree->header()->setSectionResizeMode(QHeaderView::Stretch);

    // setting up right table
    m_tableView->setModel(m_horizontalViewModel.get());
    m_tableView->setItemDelegate(m_delegate.get());
    m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ModelEditorWidget::~ModelEditorWidget() = default;

QBoxLayout* ModelEditorWidget::create_left_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_verticalTree);
    return result;
}

QBoxLayout* ModelEditorWidget::create_right_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_horizontalTree);
    result->addWidget(m_tableView);
    return result;
}

} // namespace CellEditors
