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
#include <QMenu>
#include <QTreeView>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/viewmodel/defaultviewmodel.h>
#include <mvvm/viewmodel/topitemsviewmodel.h>
#include <mvvm/viewmodel/viewitem.h>
#include <mvvm/widgets/standardtreeviews.h>
#include <mvvm/widgets/propertyflatview.h>

using namespace ModelView;

namespace
{
const QString text = "Demonstrates automatic generation of property editors in grid layout from item properties.\n"
                     "Tree on the left is showing content of our model (use mouse to select items). "
                     "Tree in the top-right corner shows standard property tree of currently "
                     "selected item. Widget in bottom-right corner shows grid layout automatically populated "
                     "with editors.";
}

DemoWidget::DemoWidget(SessionModel* model, QWidget* parent)
    : QWidget(parent), m_defaultTreeView(new AllItemsTreeView(model)),
      m_propertyTreeView(new PropertyTreeView), m_propertyFlatView(new PropertyFlatView),
      m_sessionModel(model)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);

    mainLayout->addLayout(create_top_layout());

    auto hlayout = new QHBoxLayout;
    hlayout->addLayout(create_left_layout());
    hlayout->addLayout(create_right_layout());
    mainLayout->addLayout(hlayout);
    setLayout(mainLayout);

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

QBoxLayout* DemoWidget::create_top_layout()
{
    auto result = new QHBoxLayout;
    auto label = new QLabel(this);
    label->setText(text);
    label->setWordWrap(true);
    result->addWidget(label);
    return result;
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
