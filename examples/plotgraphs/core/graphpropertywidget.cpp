// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "graphpropertywidget.h"
#include <mvvm/widgets/itemstreeview.h>
#include <mvvm/viewmodel/standardviewmodels.h>
#include <mvvm/viewmodel/abstractviewmodel.h>
#include "graphmodel.h"
#include <QBoxLayout>
#include <QPushButton>

using namespace ModelView;

GraphPropertyWidget::GraphPropertyWidget(GraphModel* model, QWidget* parent) : QWidget(parent),
    m_treeView(new ItemsTreeView), m_model(model)
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

    m_model = model;

    m_treeView->setViewModel(Utils::CreateDefaultViewModel(model));
}

QBoxLayout* GraphPropertyWidget::create_button_layout()
{
    auto result = new QHBoxLayout;
    result->setContentsMargins(0, 0, 0, 0);

    auto button = new QPushButton("Randomize");
    button->setToolTip("Randomize data");

    auto on_randomize_data = [this]() {
        if (m_model)
            m_model->randomize_graphs();
    };
    connect(button, &QPushButton::clicked, on_randomize_data);
    result->addWidget(button);

    return result;
}
