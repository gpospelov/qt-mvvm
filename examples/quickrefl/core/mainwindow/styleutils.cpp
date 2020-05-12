// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "styleutils.h"
#include <QDebug>
#include <QFont>
#include <QFontMetrics>
#include <QSize>
#include <QWidget>

namespace
{

//! Calculates size of letter `M` for current system font settings.

QSize FindSizeOfLetterM()
{
    QWidget widget;
    QFontMetrics fontMetric(widget.font());
    auto em = fontMetric.horizontalAdvance('M');
    auto fontAscent = fontMetric.ascent();
    return QSize(em, fontAscent);
}
} // namespace

QSize StyleUtils::ToolBarIconSize()
{
    return QSize(24, 24);
}

QSize StyleUtils::DockSizeHint()
{
    return QSize(480, 360);
}

QSize StyleUtils::DockMinimumSizeHint()
{
    return QSize(320, 240);
}

QFont StyleUtils::sectionFont(bool bold)
{
    QFont result;
    result.setPointSize(result.pointSize() * 1.25);
    result.setBold(bold);
    return result;
}

//! Returns size corresponding to actual size of letter `M` for current system font settings.

QSize StyleUtils::SizeOfLetterM()
{
    static QSize result = FindSizeOfLetterM();
    return result;
}

int StyleUtils::LargeButtonHeight()
{
    const int large_button_height = 60;
    return large_button_height;
}
