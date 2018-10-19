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
#include <string>
#include "model_types.h"
#include "path.h"

class SessionItem;
class QUndoStack;
class ItemManager;
class CommandService;

class SessionModel
{
public:
    SessionModel(const std::string& model_type = {});
    virtual ~SessionModel();

    std::string modelType() const;

    SessionItem* insertNewItem(const model_type& modelType, SessionItem* parent = nullptr,
                               int row = -1);

    SessionItem* rootItem() const;

    QVariant data(SessionItem* item, int role) const;

    bool setData(SessionItem* item, const QVariant& value, int role);

    Path pathFromItem(SessionItem* item);
    SessionItem* itemFromPath(Path path);

    void setUndoRedoEnabled(bool value);
    void setCommandRecordPause(bool value);

    QUndoStack* undoStack() const;

    ItemManager* manager();

    void removeRow(SessionItem* parent, int row);

private:
    void createRootItem();

    SessionItem* m_root_item;
    std::unique_ptr<CommandService> m_commands;
    std::unique_ptr<ItemManager> m_item_manager;
    std::string m_model_type;
};

#endif
