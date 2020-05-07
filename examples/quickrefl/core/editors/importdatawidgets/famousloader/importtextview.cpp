// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "importtextview.h"

#include <QAbstractTextDocumentLayout>
#include <QPainter>
#include <QScrollBar>
#include <QTextBlock>
#include <QTextDocument>

namespace DataImportGui
{

ImportTextView::ImportTextView(QWidget* parent) : QTextEdit(parent)
{
    setReadOnly(true);
    lineNumberArea = new LineNumberArea(this);

    connect(this->document(), &QTextDocument::blockCountChanged, this,
            &ImportTextView::updateLineNumberAreaWidth);
    connect(this->document()->documentLayout(), &QAbstractTextDocumentLayout::update, this,
            &ImportTextView::updateLineNumberArea);
    connect(this, &ImportTextView::cursorPositionChanged, this,
            &ImportTextView::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
    setLineWrapMode(QTextEdit::NoWrap);
}

int ImportTextView::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, document()->blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void ImportTextView::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void ImportTextView::updateLineNumberArea(const QRectF& rect)
{
    lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void ImportTextView::resizeEvent(QResizeEvent* e)
{
    QTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void ImportTextView::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

//! Get the first visible block id
int ImportTextView::getFirstVisibleBlockId()
{
    QTextCursor curs = QTextCursor(this->document());
    curs.movePosition(QTextCursor::Start);
    for (int i = 0; i < this->document()->blockCount(); ++i) {
        QTextBlock block = curs.block();

        QRect r1 = this->viewport()->geometry();
        QRect r2 = this->document()
                       ->documentLayout()
                       ->blockBoundingRect(block)
                       .translated(this->viewport()->geometry().x(),
                                   this->viewport()->geometry().y()
                                       - (this->verticalScrollBar()->sliderPosition()))
                       .toRect();

        if (r1.contains(r2, true)) {
            return i;
        }

        curs.movePosition(QTextCursor::NextBlock);
    }

    return 0;
}

void ImportTextView::lineNumberAreaPaintEvent(QPaintEvent* event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    int blockNumber = this->getFirstVisibleBlockId();
    QTextBlock block = this->document()->findBlockByNumber(blockNumber);
    QTextBlock prev_block =
        (blockNumber > 0) ? this->document()->findBlockByNumber(blockNumber - 1) : block;
    int translate_y = (blockNumber > 0) ? -this->verticalScrollBar()->sliderPosition() : 0;
    int top = this->viewport()->geometry().top();
    int additional_margin;
    if (blockNumber == 0)
        // Simply adjust to document's margin
        additional_margin = (int)this->document()->documentMargin() - 1
                            - this->verticalScrollBar()->sliderPosition();
    else
        // Getting the height of the visible part of the previous "non entirely visible" block
        additional_margin = (int)this->document()
                                ->documentLayout()
                                ->blockBoundingRect(prev_block)
                                .translated(0, translate_y)
                                .intersected(this->viewport()->geometry())
                                .height();

    // Shift the starting point
    top += additional_margin;
    int bottom = top + (int)this->document()->documentLayout()->blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(document()->documentLayout()->blockBoundingRect(block).height());
        ++blockNumber;
    }
}
} // namespace DataImportGui
