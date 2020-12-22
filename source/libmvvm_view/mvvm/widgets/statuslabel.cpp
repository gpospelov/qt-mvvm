// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/widgets/statuslabel.h"
#include "mvvm/editors/styleutils.h"
#include "mvvm/widgets/widgetutils.h"
#include <QColor>
#include <QFont>
#include <QPainter>

using namespace ModelView;

StatusLabel::StatusLabel(QWidget* parent)
    : QFrame(parent), m_font("Monospace", Style::DefaultInfoBarTextSize(), QFont::Normal, false)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setFixedHeight(Style::DefaultInfoBarHeight());
}

void StatusLabel::setText(const QString& text)
{
    m_text = text;
    update();
}

void StatusLabel::setFont(const QFont& font)
{
    m_font = font;
    update();
}

void StatusLabel::setPointSize(int pointSize)
{
    m_font.setPointSize(pointSize);
    update();
}

void StatusLabel::setAlignment(Qt::Alignment alignment)
{
    m_alignment = alignment;
    update();
}

void StatusLabel::paintEvent(QPaintEvent* event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setBrush(QColor(Qt::black));
    painter.setPen(QColor(Qt::black));
    painter.setFont(m_font);

    QRect bbox(0, 0, geometry().width(), geometry().height());
    const int gap(Utils::WidthOfLetterM() / 2); // make it smaller
    auto textRect = bbox.adjusted(gap, 0, gap, 0);

    painter.fillRect(bbox, QColor(Qt::white));
    painter.drawText(textRect, static_cast<int>(m_alignment), m_text);
}
