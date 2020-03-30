// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHEDITORTOOLBAR_H
#define GRAPHEDITORTOOLBAR_H

#include <QToolBar>

//! Narrow vertical toolbar for GraphEditor.

class GraphEditorToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit GraphEditorToolBar(QWidget* parent = nullptr);
};

#endif // GRAPHEDITORTOOLBAR_H
