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

//! Shows content of the model as vertical tree, horizontal tree and table.

class ModelEditorWidget : public QWidget {
    Q_OBJECT

public:
    explicit ModelEditorWidget(SampleModel* model = nullptr, QWidget* parent = nullptr);
    void setModel(SampleModel* model);

private:
    NodeEditor::GraphicsScene* m_graphicsScene{nullptr};
    NodeEditor::GraphicsView* m_graphicsView{nullptr};
    QSplitter* m_splitter{nullptr};
    PropertyWidget* m_propertyWidget{nullptr};
};

} // namespace NodeEditor

#endif // MODELEDITORWIDGET_H
