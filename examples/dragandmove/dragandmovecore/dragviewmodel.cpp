// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "dragviewmodel.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/viewmodel/viewmodelutils.h"
#include "mvvm/widgets/widgetutils.h"
#include <QByteArray>
#include <QDataStream>
#include <QMimeData>
#include <algorithm>

namespace {
const QString AppMimeType = "application/org.bornagainproject.moveitem";
} // namespace

using namespace ModelView;

namespace DragAndMove {

DragViewModel::DragViewModel(SessionModel* model, QObject* parent)
    : PropertyTableViewModel(model, parent)
{
}

Qt::ItemFlags DragViewModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags default_flags = PropertyTableViewModel::flags(index);
    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | default_flags;
    return Qt::ItemIsDropEnabled | default_flags;
}

QMimeData* DragViewModel::mimeData(const QModelIndexList& index_list) const
{
    auto mime_data = new QMimeData;
    auto items = Utils::ParentItemsFromIndex(index_list);

    // Saving list of SessionItem's identifiers related to all DemoItem

    QStringList identifiers;
    for (auto item : Utils::ParentItemsFromIndex(index_list))
        identifiers.append(QString::fromStdString(item->identifier()));

    mime_data->setData(AppMimeType, Utils::serialize(identifiers));
    return mime_data;
}

Qt::DropActions DragViewModel::supportedDragActions() const
{
    return Qt::TargetMoveAction;
}

Qt::DropActions DragViewModel::supportedDropActions() const
{
    return Qt::TargetMoveAction;
}

bool DragViewModel::canDropMimeData(const QMimeData* data, Qt::DropAction, int, int,
                                    const QModelIndex&) const
{
    return data->hasFormat(AppMimeType);
}

bool DragViewModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                                 const QModelIndex& parent)
{
    if (!canDropMimeData(data, action, row, column, parent))
        return false;

    int requested_row = parent.isValid() ? parent.row() : row;

    // retrieving list of item identifiers and accessing items
    auto identifiers = Utils::deserialize(data->data(AppMimeType));
    for (const auto& id : identifiers) {
        auto item = sessionModel()->findItem(id.toStdString());

        int row = std::clamp(requested_row, 0, item->parent()->itemCount(item->tagRow().tag) - 1);
        sessionModel()->moveItem(item, rootSessionItem(), {"", row});
    }

    return false;
}

} // namespace DragAndMove
