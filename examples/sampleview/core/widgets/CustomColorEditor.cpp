// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "CustomColorEditor.h"
#include <QColorDialog>
#include <QHBoxLayout>

CustomColorEditor::CustomColorEditor(QWidget*)
    : QColorDialog(QColor(Qt::blue)) // deliberately let the editor be disentangled from any parents
{
    connect(this, &QColorDialog::colorSelected, this, &CustomColorEditor::userColorChanged);
}

QColor CustomColorEditor::userColor() const
{
    return currentColor();
}

void CustomColorEditor::setUserColor(const QColor& color)
{
    if (currentColor() == color)
        return;

    setCurrentColor(color);
}
