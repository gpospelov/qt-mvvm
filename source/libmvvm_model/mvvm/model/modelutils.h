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

#include "mvvm/factories/modelconverterfactory.h"
#include "mvvm/model/itemutils.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/model_export.h"
#include <memory>
#include <vector>

namespace ModelView {

class Path;

namespace Utils {

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

//! Constructs path to find given item. Item must belong to a model.
MVVM_MODEL_EXPORT Path PathFromItem(const SessionItem* item);

//! Returns item found in the model following given Path.
MVVM_MODEL_EXPORT SessionItem* ItemFromPath(const SessionModel& moodel, const Path& path);

//! Populate empty model with content of target model using provided converter.
//! Serves as auxiliary function for model copying and cloning.
MVVM_MODEL_EXPORT void PopulateEmptyModel(const JsonModelConverterInterface* converter,
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
MVVM_MODEL_EXPORT void DeleteItemFromModel(SessionItem* item);

//! Moves item up (decrements row of the item). Works on children belonging to single tag.
MVVM_MODEL_EXPORT void MoveUp(SessionItem* item);

//! Moves item down (increments row of the item). Works on children belonging to single tag.
MVVM_MODEL_EXPORT void MoveDown(SessionItem* item);

//! Undo last model operation. If not undo/redo enabled, will do nothing.
MVVM_MODEL_EXPORT void Undo(SessionModel& model);

//! Redo model operation which was undone just before. If not undo/redo enabled, will do nothing.
MVVM_MODEL_EXPORT void Redo(SessionModel& model);

//! Begin undo/redo macros with given name. Works only if item belongs to the model, and model has
//! undo/redo enabled. Otherwise, do nothing.
MVVM_MODEL_EXPORT void BeginMacros(const SessionItem* item, const std::string& macro_name);

//! Finishes undo/redo macros. Works only if item belongs to the model, and model has undo/redo
//! enabled. Otherwise, do nothing.
MVVM_MODEL_EXPORT void EndMacros(const SessionItem* item);

//! Begin undo/redo macros with given name. Works only if the model has undo/redo enabled.
//! Otherwise, do nothing.
MVVM_MODEL_EXPORT void BeginMacros(const SessionModel* model, const std::string& macro_name);

//! Finishes undo/redo macros. Works only if the model has undo/redo enabled. Otherwise, do nothing.
MVVM_MODEL_EXPORT void EndMacros(const SessionModel* model);

} // namespace Utils
} // namespace ModelView

#endif // MVVM_MODEL_MODELUTILS_H
