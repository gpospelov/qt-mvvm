// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QColor>
#include <mvvm/model/comboproperty.h>
#include <mvvm/standarditems/plottableitems.h>

using namespace ModelView;

namespace
{
//! Following Qt styles.
const ComboProperty penStyleCombo = ComboProperty::createFrom(
    {"NoPen", "SolidLine", "DashLine", "DotLine", "DashDotLine", "DashDotDotLine"}, "SolidLine");
const int pen_default_width = 1;
const int pen_min_width = 0;
const int pen_max_width = 7;
const int penstyle_index_solid = 1;
const int penstyle_index_dashline = 2;
} // namespace

TextItem::TextItem() : CompoundItem(Constants::TextItemType)
{
    addProperty(P_TEXT, "")->setDisplayName("Text");
    addProperty(P_FONT, "Noto Sans")->setDisplayName("Font");
    addProperty(P_SIZE, 10)->setDisplayName("Size");
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
