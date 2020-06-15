// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "dataviewmodel.h"
#include "datarowstrategy.h"
#include "item_constants.h"
#include "realdatamodel.h"

#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QMimeData>

#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/viewmodel/viewmodelcontroller.h>
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

DataViewModel::DataViewModel(RealDataModel* model, QObject* parent)
    : TopItemsViewModel(model, parent)
{
    auto controller = viewModelController();
    controller->setRowStrategy(std::make_unique<DataRowStrategy>());
}

//! Return the Qt flags depending on the provided modelindex
Qt::ItemFlags DataViewModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags defaultFlags = TopItemsViewModel::flags(index);

    if (index.isValid())
        if (dynamic_cast<RealDataModel*>(sessionModel())->dragEnabled(sessionItemFromIndex(index)))
            defaultFlags = Qt::ItemIsDragEnabled | defaultFlags;
    if (dynamic_cast<RealDataModel*>(sessionModel())->dropEnabled(sessionItemFromIndex(index)))
        defaultFlags = Qt::ItemIsDropEnabled | defaultFlags;
    if (dynamic_cast<RealDataModel*>(sessionModel())->itemEditable(sessionItemFromIndex(index)))
        defaultFlags = Qt::ItemIsEditable | defaultFlags;

    return defaultFlags;
}

//! Generate the mime data
QMimeData* DataViewModel::mimeData(const QModelIndexList& index_list) const
{
    auto mimeData = new QMimeData;
    auto items = Utils::ItemsFromIndex(index_list);

    // Get the list of the identifiers
    QStringList identifiers;
    for (auto item : Utils::ItemsFromIndex(index_list))
        identifiers.append(QString::fromStdString(item->identifier()));

    mimeData->setData(QString::fromStdString(::Constants::RawDataMimeType), serialize(identifiers));
    return mimeData;
}

//! Supported drag actions
Qt::DropActions DataViewModel::supportedDragActions() const
{
    return Qt::TargetMoveAction;
}

//! Supported drop actions
Qt::DropActions DataViewModel::supportedDropActions() const
{
    return Qt::TargetMoveAction;
}

bool DataViewModel::canDropMimeData(const QMimeData* data, Qt::DropAction action, int row,
                                    int column, const QModelIndex& parent) const
{
    if (!data->hasFormat(QString::fromStdString(::Constants::RawDataMimeType)))
        return false;

    return true;
}

bool DataViewModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                                 const QModelIndex& parent)
{
    if (!canDropMimeData(data, action, row, column, parent))
        return false;

    int requested_row = parent.isValid() ? parent.row() : row;
    // retrieving list of item identifiers and accessing items
    auto identifiers =
        deserialize(data->data(QString::fromStdString(::Constants::RawDataMimeType)));
    for (auto id : identifiers) {
        auto item = sessionModel()->findItem(id.toStdString());
        auto tag = item->tag();
        int row = std::clamp(
            requested_row, 0,
            sessionItemFromIndex(parent)->itemCount(sessionItemFromIndex(parent)->defaultTag())
                - 1);
        if (!dynamic_cast<RealDataModel*>(sessionModel())
                 ->dragDropItem(item, sessionItemFromIndex(parent), row))
            return false;
    }

    return true;
}
