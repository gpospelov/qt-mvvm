// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYEREDITOR_H
#define LAYEREDITOR_H

#include <QWidget>

class SampleModel;
class LayerEditorActions;
class LayerEditorToolBar;
class LayerEditorWidget;

namespace ModelView
{
class AbstractViewModel;
}

//! Layer editor.

class LayerEditor : public QWidget
{
    Q_OBJECT
public:
    LayerEditor(SampleModel* model, QWidget* parent = nullptr);
    ~LayerEditor();

private:
    SampleModel* sample_model{nullptr};
    LayerEditorActions* actions{nullptr};
    LayerEditorToolBar* toolbar{nullptr};
    LayerEditorWidget* editor_widget{nullptr};
};

#endif // LAYEREDITOR_H
