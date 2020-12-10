// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "containereditorwidget.h"
#include "samplemodel.h"
#include <QBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QTreeView>
#include <mvvm/model/modelutils.h>
#include <mvvm/viewmodel/propertytableviewmodel.h>
#include <mvvm/viewmodel/viewmodeldelegate.h>
#include <mvvm/viewmodel/viewmodelutils.h>
#include <mvvm/widgets/widgetutils.h>

using namespace ModelView;

ContainerEditorWidget::ContainerEditorWidget(QWidget* parent)
    : QWidget(parent)
    , m_treeView(new QTreeView)
    , m_delegate(std::make_unique<ViewModelDelegate>())
    , m_model(nullptr)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

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

    // setting up the tree
    m_viewModel = std::make_unique<ModelView::PropertyTableViewModel>(model);
    m_viewModel->setRootSessionItem(root_item);
    m_treeView->setModel(m_viewModel.get());
    m_treeView->setItemDelegate(m_delegate.get());
    m_treeView->expandAll();
    m_treeView->header()->setSectionResizeMode(QHeaderView::Stretch);
    m_treeView->setSelectionMode(QAbstractItemView::ContiguousSelection);
}

QSize ContainerEditorWidget::sizeHint() const
{
    const auto panel_width = ModelView::Utils::WidthOfLetterM() * 32;
    return QSize(panel_width, panel_width * 2);
}

QSize ContainerEditorWidget::minimumSizeHint() const
{
    const auto minimum_panel_width = ModelView::Utils::WidthOfLetterM() * 16;
    return QSize(minimum_panel_width, minimum_panel_width * 2);
}

void ContainerEditorWidget::onAdd()
{
    m_model->appendNewItem(m_viewModel->rootSessionItem());
}

void ContainerEditorWidget::onCopy()
{
    for (auto item : selected_items())
        m_model->copyItem(item, m_viewModel->rootSessionItem());
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
