// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef SESSIONMODEL_H
#define SESSIONMODEL_H

#include <QVariant>
#include <memory>
#include "path.h"

class SessionItem;
class QUndoStack;

class SessionModel
{
public:
    SessionModel();
    virtual ~SessionModel();

    SessionItem* insertNewItem(SessionItem* parent = nullptr, int row = -1);

    SessionItem* rootItem() const;

    QVariant data(SessionItem* item) const;

    bool setData(SessionItem* item, const QVariant& value);

    Path pathFromItem(SessionItem* item);
    SessionItem* itemFromPath(Path path);

    void setUndoRedoEnabled(bool value);

    QUndoStack *undoStack() const;

private:
    void createRootItem();

    SessionItem* m_root_item;
    std::unique_ptr<QUndoStack> m_undoStack;
};

#endif
