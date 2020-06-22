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

#include <mvvm_model_export.h>
#include <mvvm/model/itemutils.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
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
        if (auto item = dynamic_cast<T*>(child))
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
        if (auto concrete = dynamic_cast<T*>(item))
            result.push_back(concrete);
    };

    iterate(model->rootItem(), func);

    return result;
}

void MVVM_MODEL_EXPORT DeleteItemFromModel(SessionItem* item);
void MVVM_MODEL_EXPORT MoveUp(SessionItem* item);
void MVVM_MODEL_EXPORT MoveDown(SessionItem* item);

} // namespace Utils
} // namespace ModelView

#endif // MVVM_MODEL_MODELUTILS_H
