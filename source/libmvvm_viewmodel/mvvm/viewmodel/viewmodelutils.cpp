// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QStandardItemModel>
#include <mvvm/model/customvariants.h>
#include <mvvm/model/externalproperty.h>
#include <mvvm/model/mvvm_types.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/viewmodel/abstractviewmodel.h>
#include <mvvm/viewmodel/viewitem.h>
#include <mvvm/viewmodel/viewmodelutils.h>
#include <set>

using namespace ModelView;

void Utils::iterate_model(const QStandardItemModel* model, const QModelIndex& parent,
                          std::function<void(QStandardItem*)> fun)
{
    if (!model)
        return;

    for (int row = 0; row < model->rowCount(parent); ++row) {
        for (int col = 0; col < model->columnCount(parent); ++col) {
            auto index = model->index(row, col, parent);
            auto item = model->itemFromIndex(index);
            if (item)
                fun(item);
        }
        for (int col = 0; col < model->columnCount(parent); ++col) {
            auto index = model->index(row, col, parent);
            iterate_model(model, index, fun);
        }
    }
}

std::vector<ViewItem*> Utils::findViews(const QStandardItemModel* model,
                                        const ModelView::SessionItem* item,
                                        const QModelIndex& parent)
{
    std::vector<ViewItem*> result;
    iterate_model(model, parent, [&](QStandardItem* standard_item) {
        if (auto view = dynamic_cast<ViewItem*>(standard_item)) {
            if (view->item() == item)
                result.push_back(view);
        }
    });

    return result;
}

//! Translates SessionItem's data role to vector of Qt roles.

QVector<int> Utils::item_role_to_qt(int role)
{
    QVector<int> result;
    // In Qt when we are editing the data in a view two roles are emmited.
    if (role == ItemDataRole::DISPLAY || role == ItemDataRole::DATA)
        result = {Qt::DisplayRole, Qt::EditRole};
    else if (role == ItemDataRole::APPEARANCE)
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
        result = {Qt::ForegroundRole};
#else
        result = {Qt::TextColorRole};
#endif

    return result;
}

QVariant Utils::TextColorRole(const SessionItem& item)
{
    return item.isEnabled() ? QVariant() : QColor(Qt::gray);
}

QVariant Utils::CheckStateRole(const SessionItem& item)
{
    auto value = item.data();
    if (Utils::IsBoolVariant(value))
        return value.value<bool>() ? Qt::Checked : Qt::Unchecked;
    return QVariant();
}

QVariant Utils::DecorationRole(const SessionItem& item)
{
    auto value = item.data();
    if (Utils::IsColorVariant(value))
        return value;
    else if (Utils::IsExtPropertyVariant(value))
        return value.value<ExternalProperty>().color();
    return QVariant();
}

std::vector<SessionItem*> Utils::ParentItemsFromIndex(const QModelIndexList& index_list)
{
    if (index_list.empty())
        return {};

    std::vector<SessionItem*> result;

    if (auto model = dynamic_cast<const AbstractViewModel*>(index_list.front().model())) {
        std::set<SessionItem*> unique_parents;
        for (auto index : index_list) {
            auto property_item = model->sessionItemFromIndex(index);
            unique_parents.insert(property_item->parent());
        }

        std::copy(unique_parents.begin(), unique_parents.end(), std::back_inserter(result));
    }

    return result;
}
