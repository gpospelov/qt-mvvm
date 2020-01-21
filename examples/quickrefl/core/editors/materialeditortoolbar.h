// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALEDITORTOOLBAR_H
#define MATERIALEDITORTOOLBAR_H

#include <QToolBar>

class MaterialEditorActions;

//! Material editor toolbar.

class MaterialEditorToolBar : public QToolBar
{
    Q_OBJECT
public:
    MaterialEditorToolBar(MaterialEditorActions* actions, QWidget* parent = nullptr);
    ~MaterialEditorToolBar() = default;
};

#endif // MATERIALEDITORTOOLBAR_H

