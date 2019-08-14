// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "graphpropertywidget.h"
#include "itemstreeview.h"
#include "standardviewmodels.h"
#include "graphmodel.h"
#include <QBoxLayout>

using namespace ModelView;

GraphPropertyWidget::GraphPropertyWidget(GraphModel* model, QWidget* parent) : QWidget(parent),
    m_treeView(new ItemsTreeView)
{
    auto mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(10);

    mainLayout->addWidget(m_treeView);

    setLayout(mainLayout);
    setModel(model);
}

void GraphPropertyWidget::setModel(GraphModel* model)
{
    if (!model)
        return;

    m_treeView->setViewModel(Utils::CreateDefaultViewModel(model));
}
