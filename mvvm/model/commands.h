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

#include "path.h"
#include <QUndoCommand>
#include <QVariant>

class SessionModel;

class SetValueCommand : public QUndoCommand
{
public:
    SetValueCommand(SessionModel* model, Path path, const QVariant& value, int role,
                    QUndoCommand* parent = nullptr);

    void undo() override;
    void redo() override;

private:
    Path m_path;
    SessionModel* m_model;
    QVariant m_value;
    int m_role;
};

#endif
