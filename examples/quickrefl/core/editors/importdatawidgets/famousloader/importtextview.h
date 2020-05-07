// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef IMPORTTEXTVIEW_H
#define IMPORTTEXTVIEW_H

#include <QTextEdit>

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

namespace DataImportGui
{

class LineNumberArea;

class ImportTextView : public QTextEdit
{
    Q_OBJECT

public:
    ImportTextView(QWidget* parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent* event);
    int lineNumberAreaWidth();
    int getFirstVisibleBlockId();

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRectF& rect);

private:
    QWidget* lineNumberArea;
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(ImportTextView* editor) : QWidget(editor), codeEditor(editor) {}

    QSize sizeHint() const override { return QSize(codeEditor->lineNumberAreaWidth(), 0); }

protected:
    void paintEvent(QPaintEvent* event) override
    {
        codeEditor->lineNumberAreaPaintEvent(event);
        update();
    }

private:
    ImportTextView* codeEditor;
};

} // namespace DataImportGui

#endif // IMPORTTEXTVIEW_H
