// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_SESSIONMODEL_H
#define MVVM_MODEL_SESSIONMODEL_H

#include <QVariant>
#include <memory>
#include <mvvm/core/export.h>
#include <mvvm/core/types.h>
#include <mvvm/model/function_types.h>
#include <mvvm/model/path.h>
#include <mvvm/model/tagrow.h>
#include <string>

class QUndoStack;

namespace ModelView
{

class SessionItem;
class ItemManager;
class CommandService;
class ModelMapper;
class ItemCatalogue;
class ItemPool;
class ItemBackupStrategy;
class ItemFactoryInterface;
class ItemCopyStrategy;

class CORE_EXPORT SessionModel
{
public:
    explicit SessionModel(std::string model_type = {});
    SessionModel(std::string model_type, std::shared_ptr<ItemPool> pool);

    virtual ~SessionModel();

    void setItemCatalogue(std::unique_ptr<ItemCatalogue> catalogue);

    std::string modelType() const;

    SessionItem* insertNewItem(const model_type& modelType, SessionItem* parent = nullptr,
                               const TagRow& tagrow = {});

    template <typename T> T* insertItem(SessionItem* parent = nullptr, const TagRow& tagrow = {});

    SessionItem* copyItem(const SessionItem* item, SessionItem* parent, const TagRow& tagrow = {});

    SessionItem* rootItem() const;

    QVariant data(SessionItem* item, int role) const;

    bool setData(SessionItem* item, const QVariant& value, int role);

    Path pathFromItem(const SessionItem* item) const;
    SessionItem* itemFromPath(const Path& path) const;

    void setUndoRedoEnabled(bool value);

    QUndoStack* undoStack() const;

    void removeItem(SessionItem* parent, const TagRow& tagrow);

    void moveItem(SessionItem* item, SessionItem* new_parent, const TagRow& tagrow);

    void register_item(SessionItem* item);
    void unregister_item(SessionItem* item);

    ModelMapper* mapper();

    void clear(std::function<void(SessionItem *)> callback = {});

    std::unique_ptr<ItemBackupStrategy> itemBackupStrategy() const;

    std::unique_ptr<ItemCopyStrategy> itemCopyStrategy() const;

    const ItemFactoryInterface* factory() const;

    SessionItem* findItem(const identifier_type& id);

    void swapRootItems(SessionModel& other);

//    void rebuildModel(std::function<void(SessionItem *)> callback);

protected:
    std::unique_ptr<ItemManager> m_item_manager;

private:
    void createRootItem();
    SessionItem* intern_insert(const item_factory_func_t& func, SessionItem* parent,
                               const TagRow& tagrow);

    std::unique_ptr<CommandService> m_commands;
    std::string m_model_type;
    std::unique_ptr<ModelMapper> m_mapper;
    std::unique_ptr<SessionItem> m_root_item;
};

template <typename T> T* SessionModel::insertItem(SessionItem* parent, const TagRow& tagrow)
{
    return static_cast<T*>(intern_insert([]() { return std::make_unique<T>(); }, parent, tagrow));
}

} // namespace ModelView

#endif // MVVM_MODEL_SESSIONMODEL_H
