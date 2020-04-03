// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef IMPORTWINDOW_H
#define IMPORTWINDOW_H

#include <QWidget>
#include <memory>

//! Main window to import user data.

class ImportWindow : public QWidget
{
    Q_OBJECT
public:
    ImportWindow(QWidget* parent = nullptr);
};

#endif //  IMPORTWINDOW_H
