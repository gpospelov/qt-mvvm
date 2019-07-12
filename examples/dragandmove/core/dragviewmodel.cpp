// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "dragviewmodel.h"
#include "item_constants.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "viewmodelutils.h"
#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QMimeData>

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
    auto items = Utils::SelectedParentItems(index_list);

    // Saving list of SessionItem's identifiers related to all DemoItem

    QStringList identifiers;
    for (auto item : Utils::SelectedParentItems(index_list))
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

    auto identifiers = deserialize(data->data(QString::fromStdString(::Constants::AppMimeType)));
    for (auto id : identifiers) {
        auto item = sessionModel()->findItem(id.toStdString());

        qDebug() << "going to move" << id << item << requested_row;
        int row = requested_row >= item->parent()->itemCount() ? -1 : requested_row;
        sessionModel()->moveItem(item, rootSessionItem(), "", row);
    }

    return false;
}
