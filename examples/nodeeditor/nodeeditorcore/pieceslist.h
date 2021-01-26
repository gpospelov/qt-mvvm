// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCORE_PIECESLIST_H
#define NODEEDITORCORE_PIECESLIST_H

#include <QListWidget>

namespace NodeEditor {

//! The list widget with all pieces, representing connectable elements of the node editor.
//! Located at the left-hand side of the ModelEditorWidget.
//! Elements from the list can be drag-and-dropped on the graphics scene.

class PiecesList : public QListWidget {
    Q_OBJECT

public:
    PiecesList(QWidget* parent = nullptr);

    static QString piecesMimeType();

    QSize sizeHint() const override;

protected:
    void startDrag(Qt::DropActions supportedActions) override;

private:
    void populateList();
    void addEntry(const QString& name);
};

} // namespace NodeEditor

#endif // NODEEDITORCORE_PIECESLIST_H
