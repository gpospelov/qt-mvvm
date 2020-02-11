// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYEREDITORTOOLBAR_H
#define LAYEREDITORTOOLBAR_H

#include <QToolBar>

class LayerEditorActions;

//! Layer editor toolbar.

class LayerEditorToolBar : public QToolBar
{
    Q_OBJECT
public:
    LayerEditorToolBar(LayerEditorActions* actions, QWidget* parent = nullptr);
    ~LayerEditorToolBar() = default;

private:
    QMenu* create_layer_menu(LayerEditorActions* editor_actions);
};

#endif // LAYEREDITORTOOLBAR_H

