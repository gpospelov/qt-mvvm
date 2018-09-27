// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "commands.h"
#include "sessionmodel.h"
#include "sessionitem.h"

SetValueCommand::SetValueCommand(SessionModel* model, Path path, const QVariant& value,
                                 QUndoCommand* parent)
    : QUndoCommand(parent)
    , m_path(path)
    , m_model(model)
    , m_value(value)
{

}

void SetValueCommand::undo()
{
    auto item = m_model->itemFromPath(m_path);
    QVariant old = item->data();
    item->setData(m_value);
    m_value = old;
}

void SetValueCommand::redo()
{
    auto item = m_model->itemFromPath(m_path);
    QVariant old = item->data();
    item->setData(m_value);
    m_value = old;
}
