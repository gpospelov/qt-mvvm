// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef COMMANDS_H
#define COMMANDS_H

#include "model_types.h"
#include "path.h"
#include <QUndoCommand>
#include <QVariant>
#include <memory>

class SessionModel;
class SessionItem;
class QJsonObject;

//! Command for unddo/redo framework to set the data of SessionItem.

class SetValueCommand : public QUndoCommand
{
public:
    SetValueCommand(SessionItem* item, const QVariant& value, int role);

    void undo() override;
    void redo() override;

private:
    QVariant m_value;
    int m_role;
    Path m_path;
    SessionModel* m_model;
};

//! Command for unddo/redo to insert new item.

class InsertNewItemCommand : public QUndoCommand
{
public:
    InsertNewItemCommand(const model_type& modelType, SessionItem* parent, int row);

    void undo() override;
    void redo() override;

private:
    Path m_parent_path;
    int m_row;
    model_type m_model_type;
    SessionModel* m_model;
};

//! Command for unddo/redo framework to remove row from a model.

class RemoveRowCommand : public QUndoCommand
{
public:
    RemoveRowCommand(SessionItem* parent, int row);

    void undo() override;
    void redo() override;

private:
    Path m_parent_path;
    int m_row;
    std::unique_ptr<QJsonObject> m_child_backup;
    SessionModel* m_model;
};

#endif
