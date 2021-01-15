// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PIECESLIST_H
#define PIECESLIST_H

#include <QListWidget>

namespace NodeEditor {

//! The list view with all pieces, representing connectable elements of the node editor.
//! Elements from the list can be drag-and-dropped on the graphics scene.

class PiecesList : public QListWidget {
    Q_OBJECT

public:
    PiecesList(QWidget* parent = nullptr);
};

} // namespace NodeEditor

#endif // PIECESLIST_H
