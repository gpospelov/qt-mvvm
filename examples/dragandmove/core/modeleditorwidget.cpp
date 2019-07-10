// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "modeleditorwidget.h"
#include "defaultviewmodel.h"
#include "propertytableviewmodel.h"
#include "samplemodel.h"
#include "viewmodeldelegate.h"
#include <QBoxLayout>
#include <QTableView>
#include <QTreeView>
#include <QHeaderView>

using namespace ModelView;

ModelEditorWidget::ModelEditorWidget(SampleModel* model, QWidget* parent)
    : QWidget(parent), m_leftTree(new QTreeView), m_rightTree(new QTreeView),
     m_delegate(std::make_unique<ViewModelDelegate>())
{
    auto mainLayout = new QHBoxLayout();
    mainLayout->setSpacing(10);

    mainLayout->addLayout(create_left_layout());
    mainLayout->addLayout(create_right_layout());

    setLayout(mainLayout);
    setModel(model);
}

void ModelEditorWidget::setModel(SampleModel* model)
{
    if (!model)
        return;

    // setting up left tree
    m_leftViewModel = std::make_unique<PropertyTableViewModel>(model);
    m_leftTree->setModel(m_leftViewModel.get());
    m_leftTree->setItemDelegate(m_delegate.get());
    m_leftTree->expandAll();
    m_leftTree->header()->setSectionResizeMode(QHeaderView::Stretch);

    // setting up right tree
    m_rightViewModel = std::make_unique<PropertyTableViewModel>(model);
    m_rightTree->setModel(m_rightViewModel.get());
    m_rightTree->setItemDelegate(m_delegate.get());
    m_rightTree->expandAll();
    m_rightTree->header()->setSectionResizeMode(QHeaderView::Stretch);
}

ModelEditorWidget::~ModelEditorWidget() = default;

QBoxLayout* ModelEditorWidget::create_left_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_leftTree);
    return result;
}

QBoxLayout* ModelEditorWidget::create_right_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_rightTree);
    return result;
}
