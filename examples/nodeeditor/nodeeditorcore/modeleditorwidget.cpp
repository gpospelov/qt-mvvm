// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "modeleditorwidget.h"
#include "graphicsscene.h"
#include "graphicsscenecontroller.h"
#include "graphicsview.h"
#include "pieceslist.h"
#include "propertywidget.h"
#include "sampleitems.h"
#include "samplemodel.h"
#include "mvvm/commands/undostack.h"
#include "mvvm/model/modelutils.h"
#include <QAction>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QSplitter>
#include <QToolBar>
#include <QUndoStack>

using namespace ModelView;

namespace NodeEditor {

ModelEditorWidget::ModelEditorWidget(SampleModel* model, QWidget* parent)
    : QWidget(parent)
    , m_toolBar(new QToolBar)
    , m_piecesList(new PiecesList)
    , m_propertyWidget(new PropertyWidget(model, this))
    , m_graphicsScene(new GraphicsScene(model, this))
    , m_graphicsView(new GraphicsView(m_graphicsScene, this))
    , m_sceneContoller(std::make_unique<GraphicsSceneController>(model, m_graphicsScene))
    , m_splitter(new QSplitter)
    , m_model(model)
{
    auto layout = new QVBoxLayout(this);
    layout->setSpacing(10);
    layout->addWidget(m_toolBar);
    layout->addLayout(createBottomLayout());

    setupSaveLoadActions();
    setupUndoRedoActions();
    setupConnections();
}

void ModelEditorWidget::setupSaveLoadActions()
{
    const int toolbar_icon_size = 24;
    m_toolBar->setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));

    // open file
    auto openAction = new QAction("&Open...", this);
    m_toolBar->addAction(openAction);
    auto onOpenAction = [&]() {
        QString fileName = QFileDialog::getOpenFileName(this);
        m_model->loadFromFile(fileName.toStdString());
    };
    connect(openAction, &QAction::triggered, onOpenAction);

    // save file
    auto saveAction = new QAction("&Save As...", this);
    m_toolBar->addAction(saveAction);

    auto onSaveAction = [&]() {
        QString fileName = QFileDialog::getSaveFileName(this);
        m_model->saveToFile(fileName.toStdString());
    };
    connect(saveAction, &QAction::triggered, onSaveAction);

    m_toolBar->addSeparator();
}

void ModelEditorWidget::setupUndoRedoActions()
{
    // delete action
    auto deleteAction = new QAction("Remove selected", this);
    connect(deleteAction, &QAction::triggered,
            [this]() { m_graphicsScene->onDeleteSelectedRequest(); });
    m_toolBar->addAction(deleteAction);

    // undo action
    auto undoAction = new QAction("Undo", this);
    connect(undoAction, &QAction::triggered, [this]() { Utils::Undo(*m_model); });
    undoAction->setDisabled(true);
    m_toolBar->addAction(undoAction);

    // redo action
    auto redoAction = new QAction("Redo", this);
    connect(redoAction, &QAction::triggered, [this]() { Utils::Redo(*m_model); });
    redoAction->setDisabled(true);
    m_toolBar->addAction(redoAction);

    // enable/disable undo/redo actions when there is something to undo
    if (m_model && m_model->undoStack()) {
        auto can_undo_changed = [undoAction, this]() {
            undoAction->setEnabled(m_model->undoStack()->canUndo());
        };
        connect(UndoStack::qtUndoStack(m_model->undoStack()), &QUndoStack::canUndoChanged,
                can_undo_changed);
        auto can_redo_changed = [this, redoAction]() {
            redoAction->setEnabled(m_model->undoStack()->canRedo());
        };
        connect(UndoStack::qtUndoStack(m_model->undoStack()), &QUndoStack::canUndoChanged,
                can_redo_changed);
    }
}

ModelEditorWidget::~ModelEditorWidget() = default;

//! Setups widget connections.

void ModelEditorWidget::setupConnections()
{
    // Propagates selection from the scene to the property widget.
    connect(m_graphicsScene, &GraphicsScene::connectableItemSelectionChanged, m_propertyWidget,
            &PropertyWidget::onSelectionRequest);

    // Propagates delete request from the graphics view to the scene.
    connect(m_graphicsView, &GraphicsView::deleteSelectedRequest, m_graphicsScene,
            &GraphicsScene::onDeleteSelectedRequest);
}

//! Creates layout to be placed under the toolbar.

QLayout* ModelEditorWidget::createBottomLayout()
{
    auto layout = new QHBoxLayout;
    m_splitter->addWidget(m_piecesList);
    m_splitter->addWidget(m_graphicsView);
    m_splitter->addWidget(m_propertyWidget);
    m_splitter->setSizes(QList<int>() << 50 << 300 << 120);
    layout->addWidget(m_splitter);
    return layout;
}

} // namespace NodeEditor
