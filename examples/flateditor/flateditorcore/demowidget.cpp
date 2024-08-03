// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "demowidget.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/widgets/propertyflatview.h"
#include "mvvm/widgets/standardtreeviews.h"
#include <QBoxLayout>
#include <QLabel>
#include <QTreeView>

using namespace ModelView;

namespace FlatEditor {

DemoWidget::DemoWidget(SessionModel* model, QWidget* parent)
    : QWidget(parent)
    , m_default_tree_view(new AllItemsTreeView(model))
    , m_property_tree_view(new PropertyTreeView)
    , m_property_flat_view(new PropertyFlatView)
    , m_sessio_model(model)
{

    auto layout = new QHBoxLayout;
    layout->addLayout(createLeftLayout());
    layout->addLayout(createRightLayout());
    layout->addLayout(layout);
    setLayout(layout);

    connectViews();
}

DemoWidget::~DemoWidget() = default;

//! Connect tree views to provide mutual item selection.

void DemoWidget::connectViews()
{
    // select items in other views when selection in m_defaultTreeView has changed
    auto on_item_selected = [this](SessionItem* item) {
        m_property_tree_view->setItem(item);
        m_property_flat_view->setItem(item);
    };
    connect(m_default_tree_view, &AllItemsTreeView::itemSelected, on_item_selected);
}

QBoxLayout* DemoWidget::createLeftLayout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_default_tree_view);
    return result;
}

QBoxLayout* DemoWidget::createRightLayout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_property_tree_view);
    result->addWidget(m_property_flat_view);
    return result;
}

} // namespace FlatEditor
