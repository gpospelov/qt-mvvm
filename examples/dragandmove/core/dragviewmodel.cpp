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
#include <QMimeData>
#include <QDebug>

namespace  {
const QString LinkMimeType = "application/org.bornagainproject.fittinglink";
}

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
    qDebug() << "DragViewModel::mimeData()" << index_list;
    auto mimeData = new QMimeData;
    return mimeData;
}

Qt::DropActions DragViewModel::supportedDragActions() const
{
    qDebug() << "DragViewModel::supportedDragActions()";
    return Qt::TargetMoveAction;
}

Qt::DropActions DragViewModel::supportedDropActions() const
{
    qDebug() << "DragViewModel::supportedDropActions()";
    return Qt::TargetMoveAction;
}

bool DragViewModel::canDropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) const
{
    qDebug() << "DragViewModel::canDropMimeData" << data << action << row << column << parent;

//    if (!data->hasFormat(QString::fromStdString(::Constants::AppMimeType)))
//           return false;

    return true;
}

bool DragViewModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
{
    qDebug() << "DragViewModel::dropMimeData" << data << action << row << column << parent;
    return false;
}
