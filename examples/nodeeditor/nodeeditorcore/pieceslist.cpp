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

const int column_width = 160;
} // namespace

namespace NodeEditor {

PiecesList::PiecesList(QWidget* parent) : QListWidget(parent)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setMaximumWidth(200);
    //    setFixedWidth(column_width);
    //    setWrapping(false);

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

QSize PiecesList::sizeHint() const
{
    return QSize(column_width, 600);
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
    addEntry(QString::fromStdString(NodeEditor::ParticleLayoutItemType));
    addEntry(QString::fromStdString(NodeEditor::SphereItemType));
    addEntry(QString::fromStdString(NodeEditor::CylinderItemType));
    addEntry(QString::fromStdString(NodeEditor::TransformationItemType));
    addEntry(QString::fromStdString(NodeEditor::LatticeItemType));
    selectionModel()->reset();
}

//! Adds entry to the list. It will be the icon (gray rectangle) with the name.

void PiecesList::addEntry(const QString& name)
{
    auto pieceItem = new QListWidgetItem;
    auto pixmap = createPixmap();
    pieceItem->setIcon(QIcon(pixmap));
    pieceItem->setData(Qt::DisplayRole, name);
    pieceItem->setData(ModelTypeRole, name);
    pieceItem->setData(PixmapRole, QVariant(pixmap));
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);

    // to make text centered under the icon, and items aligned vertically
    pieceItem->setTextAlignment(Qt::AlignCenter);
    pieceItem->setSizeHint(QSize(column_width, pixmap.height() * 1.5));

    addItem(pieceItem);
}

} // namespace NodeEditor
