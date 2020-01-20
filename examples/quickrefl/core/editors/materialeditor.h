// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALEDITOR_H
#define MATERIALEDITOR_H

#include <QWidget>

//! Material editor.

class MaterialEditor : public QWidget
{
    Q_OBJECT
public:
    MaterialEditor(QWidget* parent = nullptr);
};

#endif // MATERIALEDITOR_H

