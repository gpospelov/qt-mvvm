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

#include "global.h"
#include "model_types.h"
#include "path.h"
#include <QUndoCommand>
#include <QVariant>
#include <memory>

class QJsonObject;

namespace ModelView {

class SessionModel;
class SessionItem;

//! Command for unddo/redo framework to set the data of SessionItem.

class CORE_EXPORT SetValueCommand : public QUndoCommand
{
public:
    using result_t = bool;
    SetValueCommand(SessionItem* item, QVariant value, int role);

    void undo() override;
    void redo() override;

    result_t result() const;

private:
    QVariant m_value;
    int m_role;
    Path m_path;
    SessionModel* m_model;
    result_t m_result;
};

//! Command for unddo/redo to insert new item.

class CORE_EXPORT InsertNewItemCommand : public QUndoCommand
{
public:
    using result_t = SessionItem*;

    InsertNewItemCommand(model_type modelType, SessionItem* parent, int row, std::string tag);

    void undo() override;
    void redo() override;

    result_t result() const;

private:
    Path m_parent_path;
    int m_row;
    std::string m_tag;
    model_type m_model_type;
    SessionModel* m_model;
    result_t m_result;
};

//! Command for unddo/redo framework to remove row from a model.

class CORE_EXPORT RemoveRowCommand : public QUndoCommand
{
public:
    RemoveRowCommand(SessionItem* parent, int row);
    ~RemoveRowCommand() override;

    void undo() override;
    void redo() override;

private:
    Path m_parent_path;
    int m_row;
    std::unique_ptr<QJsonObject> m_child_backup;
    SessionModel* m_model;
};

}  // namespace ModelView

#endif
