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
#include <QPushButton>

using namespace ModelView;

GraphPropertyWidget::GraphPropertyWidget(GraphModel* model, QWidget* parent) : QWidget(parent),
    m_treeView(new ItemsTreeView)
{
    auto mainLayout = new QVBoxLayout;

    mainLayout->addLayout(create_button_layout());
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

void GraphPropertyWidget::onRunMeasurement()
{

}

QBoxLayout* GraphPropertyWidget::create_button_layout()
{
    auto result = new QHBoxLayout;
    result->setContentsMargins(0, 0, 0, 0);

    auto button = new QPushButton("Start measurements");
    button->setToolTip("Mimick signal measurements");
    connect(button, &QPushButton::clicked, this, &GraphPropertyWidget::onRunMeasurement);
    result->addWidget(button);

    return result;
}
