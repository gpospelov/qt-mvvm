// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "modeleditorwidget.h"
#include "containereditorwidget.h"
#include "samplemodel.h"
#include "mvvm/commands/undostack.h"
#include "mvvm/model/modelutils.h"
#include <QAction>
#include <QHBoxLayout>
#include <QToolBar>
#include <QToolButton>
#include <QUndoStack>
#include <cassert>

using namespace ModelView;

namespace DragAndMove {

ModelEditorWidget::ModelEditorWidget(SampleModel* model, QWidget* parent)
    : QWidget(parent)
    , m_toolBar(new QToolBar)
    , m_leftWidget(new ContainerEditorWidget)
    , m_rightWidget(new ContainerEditorWidget)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);

    auto top_layout = new QVBoxLayout;
    top_layout->addWidget(m_toolBar);

    auto container_layout = new QHBoxLayout;
    container_layout->setSpacing(10);
    container_layout->addWidget(m_leftWidget);
    container_layout->addSpacing(20);
    container_layout->addWidget(m_rightWidget);

    mainLayout->addLayout(top_layout);
    mainLayout->addLayout(container_layout);

    setLayout(mainLayout);
    setModel(model);

    setupActions();
}

void ModelEditorWidget::setModel(SampleModel* model)
{
    if (!model)
        return;

    m_model = model;

    auto containers = m_model->topItems();
    assert(containers.size() == 2);

    m_leftWidget->setModel(m_model, containers[0]);
    m_rightWidget->setModel(m_model, containers[1]);
}

void ModelEditorWidget::onUndo()
{
    Utils::Undo(*m_model);
}

void ModelEditorWidget::onRedo()
{
    Utils::Redo(*m_model);
}

void ModelEditorWidget::setupActions()
{
    const int toolbar_icon_size = 24;
    m_toolBar->setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));

    m_undoAction = new QAction("Undo", this);
    connect(m_undoAction, &QAction::triggered, this, &ModelEditorWidget::onUndo);
    m_undoAction->setDisabled(true);
    m_toolBar->addAction(m_undoAction);

    m_redoAction = new QAction("Redo", this);
    connect(m_redoAction, &QAction::triggered, this, &ModelEditorWidget::onRedo);
    m_redoAction->setDisabled(true);
    m_toolBar->addAction(m_redoAction);

    if (m_model && m_model->undoStack()) {
        auto can_undo_changed = [this]() {
            m_undoAction->setEnabled(m_model->undoStack()->canUndo());
        };
        connect(UndoStack::qtUndoStack(m_model->undoStack()), &QUndoStack::canUndoChanged,
                can_undo_changed);
        auto can_redo_changed = [this]() {
            m_redoAction->setEnabled(m_model->undoStack()->canRedo());
        };
        connect(UndoStack::qtUndoStack(m_model->undoStack()), &QUndoStack::canUndoChanged,
                can_redo_changed);
    }
}

} // namespace DragAndMove
