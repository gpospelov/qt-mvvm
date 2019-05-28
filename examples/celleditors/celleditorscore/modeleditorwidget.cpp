// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "modeleditorwidget.h"
#include "itemstreeview.h"
#include "standardviewmodels.h"
#include "samplemodel.h"
#include <QBoxLayout>
#include <QTreeView>
#include <QTableView>

using namespace ModelView;

ModelEditorWidget::ModelEditorWidget(SampleModel* model, QWidget* parent)
    : QWidget(parent), m_defaultTreeView(new ModelView::ItemsTreeView),
      m_treeView(new QTreeView), m_tableView(new QTableView)
{
    auto mainLayout = new QHBoxLayout();
    mainLayout->setSpacing(10);

    mainLayout->addLayout(create_left_layout(), 1);
    mainLayout->addLayout(create_right_layout(), 2);

    setLayout(mainLayout);
    setModel(model);
}

void ModelEditorWidget::setModel(SampleModel* model)
{
    if (!model)
        return;

    m_defaultTreeView->setViewModel(Utils::CreateDefaultViewModel(model));

}

ModelEditorWidget::~ModelEditorWidget() = default;

QBoxLayout* ModelEditorWidget::create_left_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_defaultTreeView);
    return result;
}

QBoxLayout* ModelEditorWidget::create_right_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_treeView);
    result->addWidget(m_tableView);
    return result;
}
