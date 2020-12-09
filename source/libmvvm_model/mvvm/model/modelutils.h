// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_MODELUTILS_H
#define MVVM_MODEL_MODELUTILS_H

#include <memory>
#include <mvvm/factories/modelconverterfactory.h>
#include <mvvm/model/itemutils.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/model_export.h>
#include <vector>

namespace ModelView
{

namespace Utils
{

//! Returns all top level items of given type.

template <typename T = SessionItem> std::vector<T*> TopItems(const SessionModel* model)
{
    std::vector<T*> result;
    for (auto child : model->rootItem()->children()) {
        if (auto item = dynamic_cast<T*>(child); item)
            result.push_back(item);
    }

    return result;
}

//! Returns top level item of given type.

template <typename T = SessionItem> T* TopItem(const SessionModel* model)
{
    auto items = TopItems<T>(model);
    return items.empty() ? nullptr : items.front();
}

//! Returns all items in a tree of given type.

template <typename T = SessionItem> std::vector<T*> FindItems(const SessionModel* model)
{
    std::vector<T*> result;

    auto func = [&result](SessionItem* item) {
        if (auto concrete = dynamic_cast<T*>(item); concrete)
            result.push_back(concrete);
    };

    iterate(model->rootItem(), func);

    return result;
}

//! Populate empty model with content of target model using provided converter.
//! Serves as auxiliary function for model copying and cloning.
void MVVM_MODEL_EXPORT PopulateEmptyModel(const JsonModelConverterInterface* converter,
                                          const SessionModel& source, SessionModel& target);

//! Creates full deep copy of given model. All item's ID will be generated.
template <typename T = SessionModel> std::unique_ptr<T> CreateCopy(const T& model)
{
    auto result = std::make_unique<T>();
    auto converter = CreateModelCopyConverter();
    PopulateEmptyModel(converter.get(), model, *result.get());
    return result;
}

//! Creates exact clone of given model. All item's ID will be preserved.
template <typename T = SessionModel> std::unique_ptr<T> CreateClone(const T& model)
{
    auto result = std::make_unique<T>();
    auto converter = CreateModelCloneConverter();
    PopulateEmptyModel(converter.get(), model, *result.get());
    return result;
}

//! Removes and deletes item from its model.
void MVVM_MODEL_EXPORT DeleteItemFromModel(SessionItem* item);

//! Moves item up (decrements row of the item). Works on children belonging to single tag.
void MVVM_MODEL_EXPORT MoveUp(SessionItem* item);

//! Moves item down (increments row of the item). Works on children belonging to single tag.
void MVVM_MODEL_EXPORT MoveDown(SessionItem* item);

//! Undo last model operation. If not undo/redo enabled, will do nothing.
void MVVM_MODEL_EXPORT Undo(SessionModel& model);

//! Redo model operation which was undone just before. If not undo/redo enabled, will do nothing.
void MVVM_MODEL_EXPORT Redo(SessionModel& model);

//! Begin undo/redo macros with given name. Works only if item belongs to the model, and model has
//! undo/redo enabled. Otherwise, do nothing.
void MVVM_MODEL_EXPORT BeginMacros(const SessionItem* item, const std::string& macro_name);

//! Finishes undo/redo macros. Works only if item belongs to the model, and model has undo/redo
//! enabled. Otherwise, do nothing.
void MVVM_MODEL_EXPORT EndMacros(const SessionItem* item);

} // namespace Utils
} // namespace ModelView

#endif // MVVM_MODEL_MODELUTILS_H
