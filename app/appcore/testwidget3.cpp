// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "testwidget3.h"
#include "jsonutils.h"
#include "sessionmodel.h"
#include "syntaxhighlighter.h"
#include "toy_includes.h"
#include "viewitem.h"
#include "defaultviewmodel.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QMenu>
#include <QTreeView>
#include <QVBoxLayout>
#include <QUndoView>

namespace
{
const QString text
    = "Undo/Redo basics.\n"
      "Tree view on the left is looking on our ViewModel. Use right mouse button "
      "on the left view to add/remove items, "
      "or just modify values of items. View on the right displays command stack.";
}

using namespace ModelView;

TestWidget3::TestWidget3(QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView), m_undoView(new QUndoView),
      m_viewModel(new DefaultViewModel(this)),
      m_sessionModel(new ToyItems::SampleModel)
{
    auto vlayout = new QVBoxLayout;
    vlayout->setSpacing(10);

    auto label = new QLabel(this);
    label->setText(text);
    vlayout->addWidget(label);

    auto hlayout = new QHBoxLayout;
    hlayout->addWidget(m_treeView);
    hlayout->addWidget(m_undoView);

    vlayout->addLayout(hlayout);
    setLayout(vlayout);

    init_session_model();
    m_viewModel->setSessionModel(m_sessionModel.get());

    init_tree_view(m_treeView);

}

void TestWidget3::onContextMenuRequest(const QPoint& point)
{
    QTreeView* treeView = qobject_cast<QTreeView*>(sender());

    auto item = item_from_view(treeView, point);
    auto taginfo = item->parent()->tagRowFromItem(item);

    QMenu menu;

    QAction* addItemAction = menu.addAction("Add item");

    // inserting item of same type after given item
    connect(addItemAction, &QAction::triggered, [&]() {
        m_sessionModel->insertNewItem(item->modelType(), item->parent(), taginfo.first + 1,
                                      taginfo.second);
    });

    QAction* removeItemAction = menu.addAction("Remove item");

    // removing item under the mouse
    connect(removeItemAction, &QAction::triggered,
            [&]() { m_sessionModel->removeItem(item->parent(), taginfo.first, taginfo.second); });

    menu.exec(treeView->mapToGlobal(point));
}

TestWidget3::~TestWidget3() = default;

//! Inits session model with some test content.

void TestWidget3::init_session_model()
{
    auto multi_layer = m_sessionModel->insertNewItem(ToyItems::Constants::MultiLayerType);
    auto layer = m_sessionModel->insertNewItem(ToyItems::Constants::LayerType, multi_layer);
    m_sessionModel->insertNewItem(ToyItems::Constants::ParticleType, layer);

    m_sessionModel->insertNewItem(ToyItems::Constants::LayerType, multi_layer);

    m_sessionModel->setUndoRedoEnabled(true);
    m_undoView->setStack(m_sessionModel->undoStack());
}

//! Inits QTreeView with ViewModel.

void TestWidget3::init_tree_view(QTreeView* view)
{
    view->setModel(m_viewModel);

    view->expandAll();
    view->resizeColumnToContents(0);
    view->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(view, &QTreeView::customContextMenuRequested, this, &TestWidget3::onContextMenuRequest);
}

//! Returns SessionItem corresponding to given coordinate in a view.

SessionItem* TestWidget3::item_from_view(QTreeView* view, const QPoint& point)
{
    QModelIndex index = view->indexAt(point);
    auto item = m_viewModel->itemFromIndex(index);
    auto viewItem = dynamic_cast<ViewItem*>(item);
    Q_ASSERT(viewItem);

    return viewItem->item();
}
