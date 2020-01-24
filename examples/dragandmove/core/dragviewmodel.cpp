// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "dragviewmodel.h"
#include "item_constants.h"
#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QMimeData>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/viewmodel/viewmodelutils.h>
#include <algorithm>

namespace
{
const QString LinkMimeType = "application/org.bornagainproject.fittinglink";

QByteArray serialize(const QStringList& data)
{
    QByteArray byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out << data;
    return byteArray;
}

QStringList deserialize(QByteArray byteArray)
{
    QStringList result;
    QDataStream in(&byteArray, QIODevice::ReadOnly);
    in >> result;
    return result;
}

} // namespace

using namespace ModelView;

DragViewModel::DragViewModel(SessionModel* model, QObject* parent)
    : PropertyTableViewModel(model, parent)
{
}

Qt::ItemFlags DragViewModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags defaultFlags = PropertyTableViewModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}

QMimeData* DragViewModel::mimeData(const QModelIndexList& index_list) const
{
    auto mimeData = new QMimeData;
    auto items = Utils::ParentItemsFromIndex(index_list);

    // Saving list of SessionItem's identifiers related to all DemoItem

    QStringList identifiers;
    for (auto item : Utils::ParentItemsFromIndex(index_list))
        identifiers.append(QString::fromStdString(item->identifier()));

    mimeData->setData(QString::fromStdString(::Constants::AppMimeType), serialize(identifiers));
    return mimeData;
}

Qt::DropActions DragViewModel::supportedDragActions() const
{
    return Qt::TargetMoveAction;
}

Qt::DropActions DragViewModel::supportedDropActions() const
{
    return Qt::TargetMoveAction;
}

bool DragViewModel::canDropMimeData(const QMimeData* data, Qt::DropAction action, int row,
                                    int column, const QModelIndex& parent) const
{
    qDebug() << "DragViewModel::canDropMimeData" << data << action << row << column << parent;
    if (!data->hasFormat(QString::fromStdString(::Constants::AppMimeType)))
        return false;

    return true;
}

bool DragViewModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                                 const QModelIndex& parent)
{
    if (!canDropMimeData(data, action, row, column, parent))
        return false;

    qDebug() << "DragViewModel::dropMimeData" << data << action << row << column << parent;

    int requested_row = parent.isValid() ? parent.row() : row;

    // retrieving list of item identifiers and accessing items
    auto identifiers = deserialize(data->data(QString::fromStdString(::Constants::AppMimeType)));
    for (auto id : identifiers) {
        auto item = sessionModel()->findItem(id.toStdString());

        qDebug() << "going to move" << id << item << requested_row;
        auto tag = item->parent()->tagRowOfItem(item).tag;
        int row = std::clamp(requested_row, 0, item->parent()->itemCount(tag) - 1);
        sessionModel()->moveItem(item, rootSessionItem(), {"", row});
    }

    return false;
}
