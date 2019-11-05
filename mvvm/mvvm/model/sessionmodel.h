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

#include <mvvm/model/function_types.h>
#include <mvvm/model/mvvm_export.h>
#include <mvvm/model/mvvm_types.h>
#include <mvvm/model/path.h>
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
                               const std::string& tag = {}, int row = -1);

    template <typename T>
    T* insertItem(SessionItem* parent = nullptr, const std::string& tag = {}, int row = -1);

    SessionItem* copyItem(const SessionItem* item, SessionItem* parent, const std::string& tag = {},
                          int row = -1);

    SessionItem* rootItem() const;

    QVariant data(SessionItem* item, int role) const;

    bool setData(SessionItem* item, const QVariant& value, int role);

    Path pathFromItem(const SessionItem* item) const;
    SessionItem* itemFromPath(Path path) const;

    void setUndoRedoEnabled(bool value);

    QUndoStack* undoStack() const;

    void removeItem(SessionItem* parent, const std::string& tag, int row);

    void moveItem(SessionItem* item, SessionItem* new_parent, const std::string& tag, int row);

    void register_item(SessionItem* item);
    void unregister_item(SessionItem* item);

    ModelMapper* mapper();

    void clear();

    std::unique_ptr<ItemBackupStrategy> itemBackupStrategy() const;

    std::unique_ptr<ItemCopyStrategy> itemCopyStrategy() const;

    const ItemFactoryInterface* factory() const;

    SessionItem* findItem(identifier_type id);

protected:
    std::unique_ptr<ItemManager> m_item_manager;

private:
    void createRootItem();
    SessionItem* intern_insert(item_factory_func_t func, SessionItem* parent = nullptr,
                            const std::string& tag = {}, int row = -1);

    std::unique_ptr<CommandService> m_commands;
    std::string m_model_type;
    std::unique_ptr<ModelMapper> m_mapper;
    std::unique_ptr<SessionItem> m_root_item;
};

template <typename T>
T* SessionModel::insertItem(SessionItem* parent, const std::string& tag, int row)
{
    return static_cast<T*>(intern_insert([]() { return std::make_unique<T>(); }, parent, tag, row));
}

} // namespace ModelView

#endif // MVVM_SESSIONMODEL_H
