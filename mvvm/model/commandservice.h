// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef COMMANDSERVICE_H
#define COMMANDSERVICE_H

#include "global.h"
#include "model_types.h"
#include <memory>

class QUndoStack;
class QUndoCommand;
class QVariant;

namespace ModelView {

class SessionModel;
class SessionItem;

//! Provides undo/redo for all commands of SessionModel.

class CORE_EXPORT CommandService
{
public:
    CommandService(SessionModel* model);

    void setUndoRedoEnabled(bool value);

    void push(QUndoCommand* command);

    SessionItem* insertNewItem(const model_type& modelType, SessionItem* parent, int row, std::string tag);

    bool setData(SessionItem* item, const QVariant& value, int role);

    void removeRow(SessionItem* parent, int row);

    QUndoStack* undoStack() const;

    void setCommandRecordPause(bool value);
private:
    bool provideUndo() const;

    SessionModel* m_model;
    std::unique_ptr<QUndoStack> m_commands;
    bool m_pause_record;
};

}  // namespace ModelView

#endif
