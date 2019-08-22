// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "graphwidget.h"
#include "graphpropertywidget.h"
#include "customgraphwidget.h"
#include <QBoxLayout>

using namespace ModelView;

GraphWidget::GraphWidget(GraphModel* model, QWidget* parent) : QWidget(parent),
    m_customGraphWidget(new CustomGraphWidget),
    m_propertyWidget(new GraphPropertyWidget)
{
    auto mainLayout = new QHBoxLayout();
    mainLayout->setSpacing(10);

    mainLayout->addLayout(create_left_layout(), 3);
    mainLayout->addLayout(create_right_layout(), 1);

    setLayout(mainLayout);
    setModel(model);
}

void GraphWidget::setModel(GraphModel* model)
{
    if (!model)
        return;

    m_propertyWidget->setModel(model);
}

GraphWidget::~GraphWidget() = default;

QBoxLayout* GraphWidget::create_left_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_customGraphWidget);
    return result;
}

QBoxLayout* GraphWidget::create_right_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_propertyWidget);
    return result;
}
