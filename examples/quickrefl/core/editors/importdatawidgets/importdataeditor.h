// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef IMPORTDATAEDITOR_H
#define IMPORTDATAEDITOR_H

#include <QWidget>

//! Main editor to import user data.

class ImportDataEditor : public QWidget
{
    Q_OBJECT
public:
    ImportDataEditor(QWidget* parent = nullptr);
};

#endif // IMPORTDATAEDITOR_H
