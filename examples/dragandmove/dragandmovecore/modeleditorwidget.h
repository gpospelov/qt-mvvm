// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DRAGANDMOVECORE_MODELEDITORWIDGET_H
#define DRAGANDMOVECORE_MODELEDITORWIDGET_H

#include <QWidget>
#include <memory>

class QToolBar;
class QAction;

namespace DragAndMove {

class SampleModel;
class ContainerEditorWidget;

//! Shows model content as two table-like trees.
//! It is expected that model has two containers with demo items, left tree shows first container,
//! right tree the second. It is possible to drag-and-drop items between two containers.

class ModelEditorWidget : public QWidget {
    Q_OBJECT

public:
    explicit ModelEditorWidget(SampleModel* model = nullptr, QWidget* parent = nullptr);

    void setModel(SampleModel* model);

private slots:
    void onUndo();
    void onRedo();

private:
    void setupActions();

    QToolBar* m_toolBar{nullptr};
    ContainerEditorWidget* m_leftWidget{nullptr};
    ContainerEditorWidget* m_rightWidget{nullptr};
    QAction* m_undoAction{nullptr};
    QAction* m_redoAction{nullptr};
    SampleModel* m_model{nullptr};
};

} // namespace DragAndMove

#endif // DRAGANDMOVECORE_MODELEDITORWIDGET_H
