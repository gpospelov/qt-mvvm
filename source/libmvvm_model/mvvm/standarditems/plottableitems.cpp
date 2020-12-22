// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/standarditems/plottableitems.h"
#include "mvvm/model/comboproperty.h"
#include <QColor>

using namespace ModelView;

namespace {
//! Following Qt styles.
const ComboProperty penStyleCombo = ComboProperty::createFrom(
    {"NoPen", "SolidLine", "DashLine", "DotLine", "DashDotLine", "DashDotDotLine"}, "SolidLine");
const int pen_default_width = 1;
const int pen_min_width = 0;
const int pen_max_width = 7;
const int penstyle_index_solid = 1;
const int penstyle_index_dashline = 2;

// We do not want to depend from widgetutils.h to get App default font size. Let's stick to
// hardcoded value for the moment, even if on different systems it can be not-optimal.
const int default_title_size = 10;
const std::string default_title_family = "Noto Sans";
} // namespace

TextItem::TextItem() : CompoundItem(Constants::TextItemType)
{
    addProperty(P_TEXT, "")->setDisplayName("Text");
    addProperty(P_FONT, default_title_family)->setDisplayName("Font");
    addProperty(P_SIZE, default_title_size)->setDisplayName("Size");
}

PenItem::PenItem() : CompoundItem(Constants::PenItemType)
{
    addProperty(P_COLOR, QColor(Qt::black))->setDisplayName("Color")->setToolTip("Pen color");
    addProperty(P_STYLE, penStyleCombo)->setDisplayName("Style")->setToolTip("Pen style");
    addProperty(P_WIDTH, pen_default_width)
        ->setDisplayName("Width")
        ->setLimits(RealLimits::limited(pen_min_width, pen_max_width))
        ->setToolTip("Pen width");
}

//! Sets style of the pen to represent selected object (dash line).

void PenItem::setSelected(bool is_selected)
{
    auto combo = penStyleCombo;
    combo.setCurrentIndex(is_selected ? penstyle_index_dashline : penstyle_index_solid);
    setProperty(P_STYLE, combo);
}

//! Returns color name in #RRGGBB format.
//! We do not want to expose QColor itself since it will be eventually removed.

std::string PenItem::colorName() const
{
    return property<QColor>(P_COLOR).name().toStdString();
}

//! Sets named color following schema from https://www.w3.org/TR/css-color-3/#svg-color.
//! e.g. "mediumaquamarine"
//! We do not want to expose QColor itself since it will be eventually removed.

void PenItem::setNamedColor(const std::string& named_color)
{
    setProperty(P_COLOR, QColor(QString::fromStdString(named_color)));
}
