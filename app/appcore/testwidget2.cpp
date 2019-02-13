// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "testwidget2.h"
#include "jsonutils.h"
#include "sessionmodel.h"
#include "syntaxhighlighter.h"
#include "toy_includes.h"
#include "viewitem.h"
#include "viewmodel.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QMenu>
#include <QTextEdit>
#include <QTreeView>
#include <QVBoxLayout>

namespace
{
const QString text
    = "SessionModel and ViewModel basics.\n"
      "SessionModel is exposed to Qt via ViewModel. "
      "Two tree views are looking to the same ViewModel. Use right mouse button to add/remove "
      "items.";
}

using namespace ModelView;

TestWidget2::TestWidget2(QWidget* parent)
    : QWidget(parent), m_treeView1(new QTreeView), m_treeView2(new QTreeView),
      m_plainText(new QTextEdit), m_viewModel(new ViewModel(this)),
      m_sessionModel(new ToyItems::SampleModel)
{
    auto vlayout = new QVBoxLayout;
    vlayout->setSpacing(10);

    auto label = new QLabel(this);
    label->setText(text);
    vlayout->addWidget(label);

    auto hlayout = new QHBoxLayout;
    hlayout->addWidget(m_treeView1);
    hlayout->addWidget(m_treeView2);

    vlayout->addLayout(hlayout);
    vlayout->addWidget(m_plainText);
    setLayout(vlayout);

    init_session_model();
    m_viewModel->setSessionModel(m_sessionModel.get());

    init_tree_view(m_treeView1);
    init_tree_view(m_treeView2);

    m_plainText->setReadOnly(true);
    QFont f("unexistent");
    f.setStyleHint(QFont::Monospace);
    m_plainText->setFont(f);

    auto highlighter = new SyntaxHighlighter(m_plainText->document());
}

void TestWidget2::onContextMenuRequest(const QPoint& point)
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

TestWidget2::~TestWidget2() = default;

//! Inits session model with some test content.

void TestWidget2::init_session_model()
{
    auto multi_layer = m_sessionModel->insertNewItem(ToyItems::Constants::MultiLayerType);
    auto layer = m_sessionModel->insertNewItem(ToyItems::Constants::LayerType, multi_layer);
    m_sessionModel->insertNewItem(ToyItems::Constants::ParticleType, layer);

    update_json();
}

void TestWidget2::update_json()
{
    m_plainText->setText(QString::fromStdString(JsonUtils::ModelToJsonString(*m_sessionModel)));
}

//! Inits QTreeView with ViewModel.

void TestWidget2::init_tree_view(QTreeView* view)
{
    view->setModel(m_viewModel);

    view->expandAll();
    view->resizeColumnToContents(0);
    view->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(view, &QTreeView::customContextMenuRequested, this, &TestWidget2::onContextMenuRequest);
}

//! Returns SessionItem corresponding to given coordinate in a view.

SessionItem* TestWidget2::item_from_view(QTreeView* view, const QPoint& point)
{
    QModelIndex index = view->indexAt(point);
    auto item = m_viewModel->itemFromIndex(index);
    auto viewItem = dynamic_cast<ViewItem*>(item);
    Q_ASSERT(viewItem);

    return viewItem->item();
}
