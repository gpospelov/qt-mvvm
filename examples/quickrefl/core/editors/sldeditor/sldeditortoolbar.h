// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SLDEDITORTOOLBAR_H
#define SLDEDITORTOOLBAR_H

#include <QToolBar>

class SLDEditorActions;

//! Material editor toolbar.

class SLDEditorToolBar : public QToolBar
{
    Q_OBJECT
public:
    SLDEditorToolBar(SLDEditorActions* actions, QWidget* parent = nullptr);
    ~SLDEditorToolBar() = default;

signals:
    void resetViewport();
};

#endif // SLDEDITORTOOLBAR_H
