// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "pieceslist.h"
#include "sampleitems.h"
#include "sceneutils.h"
#include "mvvm/widgets/widgetutils.h"
#include <QDrag>
#include <QMimeData>
#include <QPainter>
#include <QPixmap>

namespace {

QPixmap createPixmap()
{
    QRect rect = QRect(0, 0, ModelView::Utils::WidthOfLetterM() * 4,
                       ModelView::Utils::HeightOfLetterM() * 4);
    QPixmap pixmap(rect.width() + 1, rect.height() + 1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::white);
    painter.setBrush(NodeEditor::ConnectableViewGradient(QColor(Qt::gray), rect));
    painter.drawRoundedRect(rect, 5, 5);
    return pixmap;
}

const int ModelTypeRole = Qt::UserRole;
const int PixmapRole = Qt::UserRole + 1;
} // namespace

namespace NodeEditor {

PiecesList::PiecesList(QWidget* parent) : QListWidget(parent)
{
    setDragEnabled(true);
    setViewMode(QListView::IconMode);

    auto rect = ConnectableViewRectangle();
    setIconSize(QSize(rect.width(), rect.height()));
    setSpacing(static_cast<int>(rect.height() * 0.1));
    setAcceptDrops(false);
    setUniformItemSizes(true);

    populateList();
}

QString PiecesList::piecesMimeType()
{
    return QStringLiteral("image/x-connectable-view");
}

//! Prepare data for dragging.

void PiecesList::startDrag(Qt::DropActions)
{
    QListWidgetItem* item = currentItem();
    auto pixmap = item->data(PixmapRole).value<QPixmap>();
    QStringList dataToGo = QStringList() << item->data(Qt::UserRole).toString();

    auto mimeData = new QMimeData;
    mimeData->setData(piecesMimeType(), ModelView::Utils::serialize(dataToGo));

    auto drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(QPoint(pixmap.width() / 2, pixmap.height() / 2));

    drag->exec(Qt::CopyAction);
}

//! Populates list with icons representing ConnectableView's to drop on scene.

void PiecesList::populateList()
{
    addEntry(QString::fromStdString(NodeEditor::ParticleItemType));
    addEntry(QString::fromStdString(NodeEditor::TransformationItemType));
    selectionModel()->reset();
}

//! Adds entry to the list. It will be the icon (gray rectangle) with the name.

void PiecesList::addEntry(const QString& name)
{
    auto pieceItem = new QListWidgetItem(this);
    auto pixmap = createPixmap();
    pieceItem->setIcon(QIcon(pixmap));
    pieceItem->setData(Qt::DisplayRole, name);
    pieceItem->setData(ModelTypeRole, name);
    pieceItem->setData(PixmapRole, QVariant(pixmap));
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
}

} // namespace NodeEditor
