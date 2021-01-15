// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "pieceslist.h"
#include "mvvm/widgets/widgetutils.h"
#include "sampleitems.h"
#include "sceneutils.h"
#include <QPainter>
#include <QPixmap>

namespace {
QPixmap createPixmap()
{
    QRect rect = QRect(0, 0, ModelView::Utils::WidthOfLetterM() * 6,
                       ModelView::Utils::HeightOfLetterM() * 6);
    QPixmap pixmap(rect.width()+1, rect.height()+1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(NodeEditor::ConnectableViewGradient(QColor(Qt::gray), rect));
    painter.drawRect(rect);
    return pixmap;
}
} // namespace

namespace NodeEditor {

PiecesList::PiecesList(QWidget* parent) : QListWidget(parent)
{
    setDragEnabled(true);
    setViewMode(QListView::IconMode);

    auto rect = ConnectableViewRectangle();
    setIconSize(QSize(rect.width(), rect.height()));
    setSpacing(static_cast<int>(rect.height() * 0.1));

    setupList();
}

//! Setups list. Populates it with icons representing ConnectableView's to drop on scene.

void PiecesList::setupList()
{
    addPiece(QString::fromStdString(NodeEditor::ParticleItemType));
}

void PiecesList::addPiece(const QString& name)
{
    auto pieceItem = new QListWidgetItem(this);
    pieceItem->setIcon(QIcon(createPixmap()));
    pieceItem->setData(Qt::UserRole, name);
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
}

} // namespace NodeEditor
