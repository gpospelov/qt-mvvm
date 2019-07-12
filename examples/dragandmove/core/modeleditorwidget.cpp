// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "modeleditorwidget.h"
#include "containereditorwidget.h"
#include "samplemodel.h"
#include "modelutils.h"
#include <QHBoxLayout>
#include <QToolBar>
#include <QAction>
#include <QToolButton>
#include <QDebug>

using namespace ModelView;

ModelEditorWidget::ModelEditorWidget(SampleModel* model, QWidget* parent)
    : QWidget(parent), m_toolBar(new QToolBar), m_leftWidget(new ContainerEditorWidget),
      m_rightWidget(new ContainerEditorWidget)
{
    auto mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(10);

    auto top_layout = new QVBoxLayout();
    top_layout->addWidget(m_toolBar);

    auto container_layout = new QHBoxLayout();
    container_layout->setSpacing(10);
    container_layout->addWidget(m_leftWidget);
    container_layout->addSpacing(20);
    container_layout->addWidget(m_rightWidget);

    mainLayout->addLayout(top_layout);
    mainLayout->addLayout(container_layout);

    setLayout(mainLayout);
    setModel(model);

    init_toolbar();
}

void ModelEditorWidget::setModel(SampleModel* model)
{
    if (!model)
        return;

    auto containers = Utils::TopItems(model);
    assert(containers.size() == 2);

    m_leftWidget->setModel(model, containers[0]);
    m_rightWidget->setModel(model, containers[1]);
}

void ModelEditorWidget::onUndo()
{
    qDebug() << "onUndo";
}

void ModelEditorWidget::onRedo()
{
    qDebug() << "onRedo";
}

void ModelEditorWidget::init_toolbar()
{
    const int toolbar_icon_size = 24;
    m_toolBar->setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));

    auto undoAction = new QAction("Undo", this);
    connect(undoAction, &QAction::triggered, this, &ModelEditorWidget::onUndo);
    m_toolBar->addAction(undoAction);

    auto redoAction = new QAction("Redo", this);
    connect(redoAction, &QAction::triggered, this, &ModelEditorWidget::onUndo);
    m_toolBar->addAction(redoAction);
}
