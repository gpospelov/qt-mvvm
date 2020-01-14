// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "LayerTableViewModel.h"
#include "LayerItems.h"
#include "LayerTableViewModelController.h"
#include "item_constants.h"
#include <QMimeData>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>

using namespace ModelView;

namespace
{
SessionItem* findParent(SessionItem* item, QList<std::string> models);
QByteArray serialize(const std::string& data);
std::string deserialize(QByteArray byteArray);
} // namespace

LayerTableViewModel::LayerTableViewModel(SessionModel* model, QObject* parent)
    : AbstractViewModel(std::make_unique<LayerTableViewModelController>(this), parent)
{
    setSessionModel(model);
}

LayerTableViewModel::~LayerTableViewModel() = default;

Qt::ItemFlags LayerTableViewModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags flags =
        index.isValid() ? Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled : Qt::ItemIsDropEnabled;
    return flags | AbstractViewModel::flags(index);
}

QMimeData* LayerTableViewModel::mimeData(const QModelIndexList& index_list) const
{
    auto item = sessionItemFromIndex(index_list.front()); // assuming single row selection
    if (!item)
        return AbstractViewModel::mimeData(index_list);

    auto mimeData = new QMimeData;
    mimeData->setData(QString::fromStdString(::Constants::SampleMimeType),
                      serialize(item->identifier()));
    return mimeData;
}

Qt::DropActions LayerTableViewModel::supportedDragActions() const
{
    return Qt::TargetMoveAction;
}

Qt::DropActions LayerTableViewModel::supportedDropActions() const
{
    return Qt::TargetMoveAction;
}

bool LayerTableViewModel::canDropMimeData(const QMimeData* data, Qt::DropAction, int, int,
                                          const QModelIndex&) const
{
    return data->hasFormat(QString::fromStdString(::Constants::SampleMimeType));
}

bool LayerTableViewModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row,
                                       int column, const QModelIndex& parent)
{
    if (!canDropMimeData(data, action, row, column, parent))
        return false;

    // retrieving item id and accessing the item
    std::string id = deserialize(data->data(QString::fromStdString(::Constants::SampleMimeType)));
    auto item = sessionModel()->findItem(id);
    if (!item)
        return true;

    if (processDirectDrop(item, row, column, parent))
        return true;

    SessionItem* parent_item = parent.isValid() ? sessionItemFromIndex(parent) : rootSessionItem();
    const std::string tag = parent.isValid() ? MultiLayerItem::T_LAYERS : std::string{};
    int insert_row = findInsertionRow(item, parent_item, row);
    sessionModel()->moveItem(item, parent_item, {tag, insert_row});

    return true;
}

bool LayerTableViewModel::processDirectDrop(SessionItem* to_drop, int row, int,
                                            const QModelIndex& parent)
{
    if (row >= 0)
        return false; // dropping somewhere between existing items

    auto session_model = sessionModel();
    if (!parent.isValid()) { // placing the item in the last top-level row
        session_model->moveItem(to_drop, rootSessionItem(), {});
        return true;
    }

    auto acceptor = findParent(sessionItemFromIndex(parent),
                               {::Constants::LayerType, ::Constants::MultiLayerType});
    if (!acceptor)
        throw std::runtime_error(
            "Error in LayerTableViewModel::dropMimeData: failed to find acceptable drop sink.");

    const std::string acceptor_type = acceptor->modelType();
    if (acceptor_type == ::Constants::MultiLayerType) { // inserting as the very first item
        sessionModel()->moveItem(to_drop, acceptor, {MultiLayerItem::T_LAYERS, 0});
    } else if (acceptor_type == ::Constants::LayerType) { // inserting after the acceptor item
        SessionItem* parent_item = acceptor->parent();
        auto tagrow = parent_item->tagRowOfItem(acceptor);
        int insert_row = findInsertionRow(to_drop, parent_item, tagrow.row + 1);
        sessionModel()->moveItem(to_drop, parent_item, {tagrow.tag, insert_row});
    }

    return true;
}

int LayerTableViewModel::findInsertionRow(SessionItem* to_drop, SessionItem* new_parent,
                                          int row_candidate)
{
    int old_row = indexOfSessionItem(to_drop).front().row();
    if (to_drop->parent() == new_parent && old_row <= row_candidate)
        --row_candidate;
    return row_candidate;
}

namespace
{
// TODO: move to item or model utils
SessionItem* findParent(SessionItem* item, QList<std::string> models)
{
    while (item) {
        const std::string& current_model = item->modelType();
        for (const auto& model : models)
            if (current_model == model)
                return item;
        item = item->parent();
    }
    return nullptr;
}

QByteArray serialize(const std::string& data)
{
    QByteArray byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out << QString::fromStdString(data);
    return byteArray;
}

std::string deserialize(QByteArray byteArray)
{
    QString result;
    QDataStream in(&byteArray, QIODevice::ReadOnly);
    in >> result;
    return result.toStdString();
}
} // namespace
