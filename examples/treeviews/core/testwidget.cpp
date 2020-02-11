// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "testwidget.h"
#include <QBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QTreeView>
#include <QUndoView>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/viewmodel/defaultviewmodel.h>
#include <mvvm/viewmodel/topitemsviewmodel.h>
#include <mvvm/viewmodel/viewitem.h>
#include <mvvm/widgets/standardtreeviews.h>

using namespace ModelView;

namespace
{
const QString text = "Standard tree views and undo/redo basics.\n"
                     "Tree view on the left is looking on our ViewModel. Use right mouse button "
                     "on the left view to add/remove items, "
                     "or just modify values of items. View on the right displays command stack.";
}

TestWidget::TestWidget(SessionModel* model, QWidget* parent)
    : QWidget(parent), m_undoView(new QUndoView), m_defaultTreeView(new AllItemsTreeView(model)),
      m_topItemView(new TopItemsTreeView(model)), m_subsetTreeView(new AllItemsTreeView(model)),
      m_propertyTreeView(new PropertyTreeView), m_sessionModel(model)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);

    mainLayout->addLayout(create_top_layout());

    auto hlayout = new QHBoxLayout;
    hlayout->addLayout(create_left_layout());
    hlayout->addLayout(create_middle_layout());
    hlayout->addLayout(create_right_layout());
    mainLayout->addLayout(hlayout);
    setLayout(mainLayout);

    connect_views();

    m_sessionModel->setUndoRedoEnabled(true);
    m_undoView->setStack(m_sessionModel->undoStack());
}

TestWidget::~TestWidget() = default;

void TestWidget::onContextMenuRequest(const QPoint& point)
{
    auto treeView = qobject_cast<QTreeView*>(sender());

    auto item = item_from_view(treeView, point);
    auto tagrow = item->parent()->tagRowOfItem(item);

    QMenu menu;

    // inserting item of same type after given item
    auto addItemAction = menu.addAction("Add item");
    auto add_item = [&]() {
        m_sessionModel->insertNewItem(item->modelType(), item->parent(), tagrow.next());
    };
    connect(addItemAction, &QAction::triggered, add_item);

    // removing item under the mouse
    auto removeItemAction = menu.addAction("Remove item");
    auto remove_item = [&]() { m_sessionModel->removeItem(item->parent(), tagrow); };
    connect(removeItemAction, &QAction::triggered, remove_item);

    menu.exec(treeView->mapToGlobal(point));
}

//! Returns SessionItem corresponding to given coordinate in a view.

SessionItem* TestWidget::item_from_view(QTreeView* view, const QPoint& point)
{
    QModelIndex index = view->indexAt(point);
    auto item = m_defaultTreeView->viewModel()->itemFromIndex(index);
    auto viewItem = dynamic_cast<ViewItem*>(item);
    Q_ASSERT(viewItem);
    return viewItem->item();
}

//! Connect tree views to provide mutual item selection.

void TestWidget::connect_views()
{
    // select items in other views when selection in m_defaultTreeView has changed
    auto on_item_selected = [this](SessionItem* item) {
        m_subsetTreeView->setRootSessionItem(item);
        m_propertyTreeView->setItem(item);
        m_topItemView->setSelected(item);
    };
    connect(m_defaultTreeView, &AllItemsTreeView::itemSelected, on_item_selected);

    m_defaultTreeView->treeView()->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_defaultTreeView->treeView(), &QTreeView::customContextMenuRequested, this,
            &TestWidget::onContextMenuRequest);

    // will notify m_defaultTreeView
    auto on_top_item_selected = [this](SessionItem* item) { m_defaultTreeView->setSelected(item); };
    connect(m_topItemView, &TopItemsTreeView::itemSelected, on_top_item_selected);
}

QBoxLayout* TestWidget::create_top_layout()
{
    auto result = new QHBoxLayout;
    auto label = new QLabel(this);
    label->setText(text);
    label->setWordWrap(true);
    result->addWidget(label);
    return result;
}

QBoxLayout* TestWidget::create_left_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_defaultTreeView);
    return result;
}

QBoxLayout* TestWidget::create_middle_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_topItemView);
    result->addWidget(m_subsetTreeView);
    return result;
}

QBoxLayout* TestWidget::create_right_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_undoView);
    result->addWidget(m_propertyTreeView);
    return result;
}
