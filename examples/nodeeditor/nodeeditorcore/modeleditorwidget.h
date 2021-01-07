// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MODELEDITORWIDGET_H
#define MODELEDITORWIDGET_H

#include <QWidget>
#include <memory>

class QSplitter;

namespace NodeEditor {

class SampleModel;
class GraphicsView;
class GraphicsScene;
class PropertyWidget;

//! Main widget for model editing. Contains a graphics scene with node editor on the left,
//! and property panel on the right. Belongs to MainWindow.

class ModelEditorWidget : public QWidget {
    Q_OBJECT

public:
    explicit ModelEditorWidget(SampleModel* model = nullptr, QWidget* parent = nullptr);

private:
    NodeEditor::GraphicsScene* m_graphicsScene{nullptr};
    NodeEditor::GraphicsView* m_graphicsView{nullptr};
    QSplitter* m_splitter{nullptr};
    PropertyWidget* m_propertyWidget{nullptr};
};

} // namespace NodeEditor

#endif // MODELEDITORWIDGET_H
