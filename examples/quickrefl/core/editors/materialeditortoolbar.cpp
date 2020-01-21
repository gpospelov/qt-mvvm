// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialeditortoolbar.h"
#include "styleutils.h"

MaterialEditorToolBar::MaterialEditorToolBar(MaterialEditorActions* actions, QWidget* parent)
    : QToolBar(parent)
{
    setIconSize(StyleUtils::ToolBarIconSize());

    addAction("Add material");
    addAction("Clone");
    addAction("Remove");
}
