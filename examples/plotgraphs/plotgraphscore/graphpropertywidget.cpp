// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphpropertywidget.h"
#include "graphmodel.h"
#include <QBoxLayout>
#include <QPushButton>
#include <mvvm/factories/viewmodelfactory.h>
#include <mvvm/viewmodel/viewmodel.h>
#include <mvvm/widgets/itemstreeview.h>

using namespace ModelView;

namespace PlotGraphs
{

GraphPropertyWidget::GraphPropertyWidget(GraphModel* model, QWidget* parent)
    : QWidget(parent), m_treeView(new ItemsTreeView), m_model(model)
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

    m_treeView->setViewModel(Factory::CreateDefaultViewModel(model));
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

} // namespace PlotGraphs
