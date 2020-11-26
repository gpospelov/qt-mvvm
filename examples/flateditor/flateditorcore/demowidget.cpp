// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "demowidget.h"
#include <QBoxLayout>
#include <QLabel>
#include <QTreeView>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/viewmodel/defaultviewmodel.h>
#include <mvvm/viewmodel/topitemsviewmodel.h>
#include <mvvm/widgets/propertyflatview.h>
#include <mvvm/widgets/standardtreeviews.h>

using namespace ModelView;

DemoWidget::DemoWidget(SessionModel* model, QWidget* parent)
    : QWidget(parent)
    , m_defaultTreeView(new AllItemsTreeView(model))
    , m_propertyTreeView(new PropertyTreeView)
    , m_propertyFlatView(new PropertyFlatView)
    , m_sessionModel(model)
{

    auto layout = new QHBoxLayout;
    layout->addLayout(create_left_layout());
    layout->addLayout(create_right_layout());
    layout->addLayout(layout);
    setLayout(layout);

    connect_views();
}

DemoWidget::~DemoWidget() = default;

//! Connect tree views to provide mutual item selection.

void DemoWidget::connect_views()
{
    // select items in other views when selection in m_defaultTreeView has changed
    auto on_item_selected = [this](SessionItem* item) {
        m_propertyTreeView->setItem(item);
        m_propertyFlatView->setItem(item);
    };
    connect(m_defaultTreeView, &AllItemsTreeView::itemSelected, on_item_selected);
}

QBoxLayout* DemoWidget::create_left_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_defaultTreeView);
    return result;
}

QBoxLayout* DemoWidget::create_right_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_propertyTreeView);
    result->addWidget(m_propertyFlatView);
    return result;
}
