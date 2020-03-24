// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "quicksimeditor.h"
#include "styleutils.h"

QuickSimEditor::QuickSimEditor(QWidget* parent) : QWidget(parent)
{
    setWindowTitle(QString("Reflectivity plot"));
}

QSize QuickSimEditor::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize QuickSimEditor::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}
