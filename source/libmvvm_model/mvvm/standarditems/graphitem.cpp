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
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/linkeditem.h>
#include <mvvm/standarditems/plottableitems.h>

using namespace ModelView;

namespace
{
const ComboProperty penStyleCombo = ComboProperty::createFrom(
    {"NoPen", "SolidLine", "DashLine", "DotLine", "DashDotLine", "DashDotDotLine"}, "SolidLine");
} // namespace

GraphItem::GraphItem(const std::string& model_type) : CompoundItem(model_type)
{
    addProperty<LinkedItem>(P_LINK)->setDisplayName("Link");
    addProperty<TextItem>(P_GRAPH_TITLE)->setDisplayName("Graph title");
    addProperty(P_COLOR, QColor(Qt::black))->setDisplayName("Color")->setToolTip("Line color");
    addProperty(P_PENSTYLE, penStyleCombo)->setDisplayName("Pen style")->setToolTip("Pen style");
    addProperty(P_PENWIDTH, 1)
        ->setDisplayName("Pen width")
        ->setLimits(RealLimits::limited(0, 7))
        ->setToolTip("Pen width");
    addProperty<PenItem>(P_PEN)->setDisplayName("Pen");
    addProperty(P_DISPLAYED, true)->setDisplayName("Displayed");
}

//! Sets link to the data item.

void GraphItem::setDataItem(const Data1DItem* data_item)
{
    item<LinkedItem>(P_LINK)->setLink(data_item);
}

//! Update item from the content of given graph. Link to the data will be set
//! as in given item, other properties copied.

void GraphItem::setFromGraphItem(const GraphItem* item)
{
    setDataItem(item->dataItem());
    setProperty(P_COLOR, item->property<QColor>(P_COLOR));
    setProperty(P_PENSTYLE, item->property<ComboProperty>(P_PENSTYLE));
    setProperty(P_PENWIDTH, item->property<int>(P_PENWIDTH));
}

//! Returns data item linked to the given GraphItem.

Data1DItem* GraphItem::dataItem() const
{
    return item<LinkedItem>(P_LINK)->get<Data1DItem>();
}

std::vector<double> GraphItem::binCenters() const
{
    return dataItem() ? dataItem()->binCenters() : std::vector<double>();
}

std::vector<double> GraphItem::binValues() const
{
    return dataItem() ? dataItem()->binValues() : std::vector<double>();
}
