// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_COMMANDADAPTER_H
#define MVVM_COMMANDS_COMMANDADAPTER_H

#include "mvvm/model_export.h"
#include <QUndoCommand>
#include <memory>

namespace ModelView {

class AbstractItemCommand;

//! Adapter to execute our commands within Qt undo/redo framework.

class MVVM_MODEL_EXPORT CommandAdapter : public QUndoCommand {
public:
    CommandAdapter(std::shared_ptr<AbstractItemCommand> command);
    ~CommandAdapter() override;

    void undo() override;
    void redo() override;

private:
    std::shared_ptr<AbstractItemCommand> m_command;
};

} // namespace ModelView

#endif // MVVM_COMMANDS_COMMANDADAPTER_H
