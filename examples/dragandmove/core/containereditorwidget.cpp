// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "containereditorwidget.h"

#include "modeleditorwidget.h"
#include "defaultviewmodel.h"
#include "propertytableviewmodel.h"
#include "samplemodel.h"
#include "viewmodeldelegate.h"
#include <QBoxLayout>
#include <QTreeView>
#include <QHeaderView>

using namespace ModelView;

ContainerEditorWidget::ContainerEditorWidget(QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView),
     m_delegate(std::make_unique<ViewModelDelegate>())
{
    auto mainLayout = new QHBoxLayout();
    mainLayout->setSpacing(10);

    mainLayout->addWidget(m_treeView);

    setLayout(mainLayout);
}

void ContainerEditorWidget::setModel(SampleModel* model)
{
    if (!model)
        return;

    // setting up left tree
    m_viewModel = std::make_unique<PropertyTableViewModel>(model);
    m_treeView->setModel(m_viewModel.get());
    m_treeView->setItemDelegate(m_delegate.get());
    m_treeView->expandAll();
    m_treeView->header()->setSectionResizeMode(QHeaderView::Stretch);
}

ContainerEditorWidget::~ContainerEditorWidget() = default;
