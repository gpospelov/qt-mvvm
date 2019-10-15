// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "testwidget.h"
#include "itemstreeview.h"
#include "propertyeditor.h"
#include "sessionmodel.h"
#include "sessionitem.h"
#include "topitemsviewmodel.h"
#include "defaultviewmodel.h"
#include "viewitem.h"
#include <QBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QTreeView>
#include <QUndoView>

using namespace ModelView;

namespace
{
const QString text = "Standard tree views and undo/redo basics.\n"
                     "Tree view on the left is looking on our ViewModel. Use right mouse button "
                     "on the left view to add/remove items, "
                     "or just modify values of items. View on the right displays command stack.";
}

TestWidget::TestWidget(SessionModel* model, QWidget* parent)
    : QWidget(parent), m_defaultTreeView(new ItemsTreeView), m_topItemView(new ItemsTreeView),
      m_subsetTreeView(new ItemsTreeView), m_undoView(new QUndoView),
      m_propertyEditor(new PropertyEditor), m_sessionModel(model)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);

    mainLayout->addLayout(create_top_layout());

    auto hlayout = new QHBoxLayout;
    hlayout->addLayout(create_left_layout());
    hlayout->addLayout(create_middle_layout());
    hlayout->addLayout(create_right_layout());
    mainLayout->addLayout(hlayout);

    init_default_view();
    init_topitems_view();
    init_subset_view();

    setLayout(mainLayout);

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
        m_sessionModel->insertNewItem(item->modelType(), item->parent(), tagrow.tag,
                                      tagrow.row + 1);
    };
    connect(addItemAction, &QAction::triggered, add_item);

    // removing item under the mouse
    auto removeItemAction = menu.addAction("Remove item");
    auto remove_item = [&]() {
        m_sessionModel->removeItem(item->parent(), tagrow.tag, tagrow.row);
    };
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

void TestWidget::init_default_view()
{
    m_defaultTreeView->setViewModel(std::make_unique<DefaultViewModel>(m_sessionModel));

    // will notify m_topItemView and chose selected item in two other editors
    auto on_item_selected = [this](SessionItem* item) {
        m_subsetTreeView->setRootSessionItem(item);
        m_propertyEditor->setItem(item);
        m_topItemView->setSelected(item);
    };

    connect(m_defaultTreeView, &ItemsTreeView::itemSelected, on_item_selected);

    m_defaultTreeView->treeView()->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_defaultTreeView->treeView(), &QTreeView::customContextMenuRequested, this,
            &TestWidget::onContextMenuRequest);
}

void TestWidget::init_topitems_view()
{
    m_topItemView->setViewModel(std::make_unique<TopItemsViewModel>(m_sessionModel));

    // will notify m_defaultTreeView
    auto on_item_selected = [this](SessionItem* item) { m_defaultTreeView->setSelected(item); };
    connect(m_topItemView, &ItemsTreeView::itemSelected, on_item_selected);
}

void TestWidget::init_subset_view()
{
    m_subsetTreeView->setViewModel(std::make_unique<DefaultViewModel>(m_sessionModel));
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
    result->addWidget(m_propertyEditor);
    return result;
}
