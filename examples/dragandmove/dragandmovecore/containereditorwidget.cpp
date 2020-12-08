// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "containereditorwidget.h"
#include "dragviewmodel.h"
#include "samplemodel.h"
#include <QBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QTreeView>
#include <mvvm/model/modelutils.h>
#include <mvvm/viewmodel/viewmodeldelegate.h>
#include <mvvm/viewmodel/viewmodelutils.h>

using namespace ModelView;

namespace DragAndView
{

ContainerEditorWidget::ContainerEditorWidget(QWidget* parent)
    : QWidget(parent)
    , m_treeView(new QTreeView)
    , m_delegate(std::make_unique<ViewModelDelegate>())
    , m_container(nullptr)
    , m_model(nullptr)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);

    mainLayout->addWidget(m_treeView);
    mainLayout->addLayout(create_button_layout());

    setLayout(mainLayout);
}

ContainerEditorWidget::~ContainerEditorWidget() = default;

void ContainerEditorWidget::setModel(SampleModel* model, SessionItem* root_item)
{
    if (!model)
        return;

    m_model = model;
    m_container = root_item;

    // setting up the tree
    m_viewModel = std::make_unique<DragViewModel>(model);
    m_viewModel->setRootSessionItem(m_container);
    m_treeView->setModel(m_viewModel.get());
    m_treeView->setItemDelegate(m_delegate.get());
    m_treeView->expandAll();
    m_treeView->header()->setSectionResizeMode(QHeaderView::Stretch);
    m_treeView->setSelectionMode(QAbstractItemView::ContiguousSelection);

    setAcceptDrops(true);
    m_treeView->setDragEnabled(true);
    m_treeView->viewport()->setAcceptDrops(true);
    m_treeView->setDropIndicatorShown(true);
}

void ContainerEditorWidget::onAdd()
{
    m_model->append_random_item(m_container);
}

void ContainerEditorWidget::onCopy()
{
    for (auto item : selected_items())
        m_model->copyItem(item, m_container);
}

void ContainerEditorWidget::onRemove()
{
    for (auto item : selected_items())
        Utils::DeleteItemFromModel(item);
}

void ContainerEditorWidget::onMoveDown()
{
    auto items = selected_items();
    std::reverse(items.begin(), items.end()); // to correctly move multiple selections
    for (auto item : selected_items())
        ModelView::Utils::MoveDown(item);
}

void ContainerEditorWidget::onMoveUp()
{
    for (auto item : selected_items())
        ModelView::Utils::MoveUp(item);
}

std::vector<SessionItem*> ContainerEditorWidget::selected_items() const
{
    return Utils::ParentItemsFromIndex(m_treeView->selectionModel()->selectedIndexes());
}

QBoxLayout* ContainerEditorWidget::create_button_layout()
{
    auto result = new QHBoxLayout;
    result->setContentsMargins(5, 5, 5, 25);

    auto button = new QPushButton("Add");
    button->setToolTip("Append new item at the bottom");
    connect(button, &QPushButton::clicked, this, &ContainerEditorWidget::onAdd);
    result->addWidget(button);

    button = new QPushButton("Copy");
    button->setToolTip("Copy selected item below");
    connect(button, &QPushButton::clicked, this, &ContainerEditorWidget::onCopy);
    result->addWidget(button);

    button = new QPushButton("Remove");
    button->setToolTip("Remove selected item");
    connect(button, &QPushButton::clicked, this, &ContainerEditorWidget::onRemove);
    result->addWidget(button);

    button = new QPushButton("Down");
    button->setToolTip("Move selected item down");
    connect(button, &QPushButton::clicked, this, &ContainerEditorWidget::onMoveDown);
    result->addWidget(button);

    button = new QPushButton("Up");
    button->setToolTip("Move selected item up");
    connect(button, &QPushButton::clicked, this, &ContainerEditorWidget::onMoveUp);
    result->addWidget(button);

    return result;
}

} // namespace DragAndView
