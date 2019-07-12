// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "containereditorwidget.h"

#include "modeleditorwidget.h"
#include "defaultviewmodel.h"
#include "propertytableviewmodel.h"
#include "samplemodel.h"
#include "viewmodeldelegate.h"
#include <QBoxLayout>
#include <QTreeView>
#include <QHeaderView>
#include <QPushButton>
#include <QDebug>

using namespace ModelView;

ContainerEditorWidget::ContainerEditorWidget(QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView),
     m_delegate(std::make_unique<ViewModelDelegate>())
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);

    mainLayout->addWidget(m_treeView);
    mainLayout->addLayout(create_button_layout());

    setLayout(mainLayout);
}

void ContainerEditorWidget::setModel(SampleModel* model, ModelView::SessionItem* root_item)
{
    if (!model)
        return;

    // setting up left tree
    m_viewModel = std::make_unique<PropertyTableViewModel>(model);
    m_viewModel->setRootSessionItem(root_item);
    m_treeView->setModel(m_viewModel.get());
    m_treeView->setItemDelegate(m_delegate.get());
    m_treeView->expandAll();
    m_treeView->header()->setSectionResizeMode(QHeaderView::Stretch);
}

void ContainerEditorWidget::onAdd()
{
    qDebug() << "onAdd";
}

void ContainerEditorWidget::onCopy()
{
    qDebug() << "onCopy";
}

void ContainerEditorWidget::onRemove()
{
    qDebug() << "onRemove";
}

void ContainerEditorWidget::onDown()
{
    qDebug() << "onDown";
}

void ContainerEditorWidget::onUp()
{
    qDebug() << "onUp";
}

QBoxLayout* ContainerEditorWidget::create_button_layout()
{
    auto result = new QHBoxLayout();
    result->setContentsMargins(5, 5, 5, 25);

    auto button = new QPushButton("Add");
    button->setToolTip("Add new item at the bottom");
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
    connect(button, &QPushButton::clicked, this, &ContainerEditorWidget::onDown);
    result->addWidget(button);

    button = new QPushButton("Up");
    button->setToolTip("Move selected item up");
    connect(button, &QPushButton::clicked, this, &ContainerEditorWidget::onUp);
    result->addWidget(button);

    return result;
}

ContainerEditorWidget::~ContainerEditorWidget() = default;
