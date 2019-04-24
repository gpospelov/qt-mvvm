// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_SESSIONMODEL_H
#define MVVM_SESSIONMODEL_H

#include "global.h"
#include "model_types.h"
#include "path.h"
#include <QVariant>
#include <memory>
#include <string>

class QUndoStack;

namespace ModelView
{

class SessionItem;
class ItemManager;
class CommandService;
class ModelMapper;

class CORE_EXPORT SessionModel
{
public:
    SessionModel(std::string model_type = {});
    virtual ~SessionModel();

    std::string modelType() const;

    SessionItem* insertNewItem(const model_type& modelType, SessionItem* parent = nullptr,
                               const std::string& tag = {}, int index = -1);

    SessionItem* rootItem() const;

    QVariant data(SessionItem* item, int role) const;

    bool setData(SessionItem* item, const QVariant& value, int role);

    Path pathFromItem(SessionItem* item);
    SessionItem* itemFromPath(Path path);

    void setUndoRedoEnabled(bool value);
    void setCommandRecordPause(bool value);

    QUndoStack* undoStack() const;

    ItemManager* manager();
    const ItemManager* manager() const;

    void removeItem(SessionItem* parent, const std::string& tag, int row);

    void register_item(SessionItem* item);
    void unregister_item(SessionItem* item);

    ModelMapper* mapper();

protected:
    std::unique_ptr<ItemManager> m_item_manager;

private:
    void createRootItem();

    std::unique_ptr<CommandService> m_commands;
    std::string m_model_type;
    std::unique_ptr<ModelMapper> m_mapper;
    std::unique_ptr<SessionItem> m_root_item;
};

} // namespace ModelView

#endif // MVVM_SESSIONMODEL_H

