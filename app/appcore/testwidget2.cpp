// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "testwidget2.h"
#include "viewitem.h"
#include "viewmodel.h"
#include "sessionmodel.h"
#include "toy_includes.h"
#include "jsonutils.h"
#include "syntaxhighlighter.h"
#include <QTreeView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMenu>
#include <QDebug>
using namespace ModelView;

TestWidget2::TestWidget2(QWidget* parent)
    : QWidget(parent)
    , m_treeView1(new QTreeView)
    , m_treeView2(new QTreeView)
    , m_plainText(new QTextEdit)
    , m_viewModel(new ViewModel(this))
    , m_sessionModel(new ToyItems::SampleModel)
{
    auto vlayout = new QVBoxLayout;

    auto hlayout = new QHBoxLayout;
    hlayout->addWidget(m_treeView1);
    hlayout->addWidget(m_treeView2);

    vlayout->addLayout(hlayout);
    vlayout->addWidget(m_plainText);
    setLayout(vlayout);

    init_session_model();
    m_viewModel->setSessionModel(m_sessionModel.get());

    m_treeView1->setModel(m_viewModel);
    m_treeView2->setModel(m_viewModel);

    m_treeView1->expandAll();
    m_treeView2->expandAll();

    m_treeView1->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_treeView1, &QTreeView::customContextMenuRequested, this,
            &TestWidget2::onContextMenuRequest);

    m_plainText->setReadOnly(true);
    QFont f("unexistent");
    f.setStyleHint(QFont::Monospace);
    m_plainText->setFont(f);

    auto highlighter = new SyntaxHighlighter(m_plainText->document());
}

void TestWidget2::onContextMenuRequest(const QPoint& point)
{
    QMenu menu;

    QAction* addItemAction = menu.addAction("Add item");

    connect(addItemAction, &QAction::triggered, [&]()
    {
        QModelIndex index = m_treeView1->indexAt(point);
        auto item = m_viewModel->itemFromIndex(index);
        auto viewItem = dynamic_cast<ViewItem*>(item);
        if (viewItem) {
            auto child = viewItem->item();
            int index = child->parent()->tagRowFromItem(child).first;
            m_sessionModel->insertNewItem(child->modelType(), child->parent(), index+1);
        }
    });

    QAction* removeItemAction = menu.addAction("Remove item");

    connect(removeItemAction, &QAction::triggered, [&]()
    {
        QModelIndex index = m_treeView1->indexAt(point);
        auto item = m_viewModel->itemFromIndex(index);
        auto viewItem = dynamic_cast<ViewItem*>(item);
        if (viewItem) {
            auto child = viewItem->item();
            auto taginfo = child->parent()->tagRowFromItem(child);
            m_sessionModel->removeItem(child->parent(), taginfo.first, taginfo.second);
        }
    });


    menu.exec(m_treeView1->mapToGlobal(point));
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
