// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALTABLEWIDGET_H
#define MATERIALTABLEWIDGET_H

#include <QWidget>

//! Widget to hold material table (MaterialTableView) and all corresponding model and delegates.
//! Belongs to MaterialEditor.

class MaterialTableWidget : public QWidget
{
    Q_OBJECT
public:
    MaterialTableWidget(QWidget* parent = nullptr);
};

#endif // MATERIALTABLEWIDGET_H
