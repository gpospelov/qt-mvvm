// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sampleeditorwidget.h"
#include <QBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QTreeView>
#include <QUndoView>
#include <mvvm/commands/undostack.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/viewmodel/defaultviewmodel.h>
#include <mvvm/viewmodel/topitemsviewmodel.h>
#include <mvvm/viewmodel/viewitem.h>
#include <mvvm/widgets/standardtreeviews.h>

using namespace ModelView;

namespace TreeViews
{

SampleEditorWdiget::SampleEditorWdiget(SessionModel* model, QWidget* parent)
    : QWidget(parent)
    , m_undoView(new QUndoView)
    , m_defaultTreeView(new AllItemsTreeView(model))
    , m_topItemView(new TopItemsTreeView(model))
    , m_subsetTreeView(new AllItemsTreeView(model))
    , m_propertyTreeView(new PropertyTreeView)
    , m_sessionModel(model)
{
    auto layout = new QHBoxLayout;
    layout->addLayout(createLeftLayout());
    layout->addLayout(createMiddleLayout());
    layout->addLayout(createRightLayout());
    setLayout(layout);

    connect_views();

    m_sessionModel->setUndoRedoEnabled(true);
    m_undoView->setStack(UndoStack::qtUndoStack(m_sessionModel->undoStack()));
}

SampleEditorWdiget::~SampleEditorWdiget() = default;

void SampleEditorWdiget::onContextMenuRequest(const QPoint& point)
{
    auto treeView = qobject_cast<QTreeView*>(sender());

    auto item = item_from_view(treeView, point);
    auto tagrow = item->tagRow();

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

SessionItem* SampleEditorWdiget::item_from_view(QTreeView* view, const QPoint& point)
{
    QModelIndex index = view->indexAt(point);
    auto view_item = m_defaultTreeView->viewModel()->itemFromIndex(index);
    return view_item->item();
}

//! Connect tree views to provide mutual item selection.

void SampleEditorWdiget::connect_views()
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
            &SampleEditorWdiget::onContextMenuRequest);

    // will notify m_defaultTreeView
    auto on_top_item_selected = [this](SessionItem* item) { m_defaultTreeView->setSelected(item); };
    connect(m_topItemView, &TopItemsTreeView::itemSelected, on_top_item_selected);
}

QBoxLayout* SampleEditorWdiget::createLeftLayout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_defaultTreeView);
    return result;
}

QBoxLayout* SampleEditorWdiget::createMiddleLayout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_topItemView);
    result->addWidget(m_subsetTreeView);
    return result;
}

QBoxLayout* SampleEditorWdiget::createRightLayout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_undoView);
    result->addWidget(m_propertyTreeView);
    return result;
}

} // namespace TreeViews
