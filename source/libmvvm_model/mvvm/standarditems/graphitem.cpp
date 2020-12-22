// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/standarditems/graphitem.h"
#include "mvvm/model/comboproperty.h"
#include "mvvm/standarditems/data1ditem.h"
#include "mvvm/standarditems/linkeditem.h"
#include "mvvm/standarditems/plottableitems.h"
#include <QColor>

using namespace ModelView;

GraphItem::GraphItem(const std::string& model_type) : CompoundItem(model_type)
{
    addProperty<LinkedItem>(P_LINK)->setDisplayName("Link");
    addProperty<TextItem>(P_GRAPH_TITLE)->setDisplayName("Graph title");
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

void GraphItem::setFromGraphItem(const GraphItem* graph_item)
{
    setDataItem(graph_item->dataItem());
    auto pen = item<PenItem>(P_PEN);
    auto source_pen = graph_item->item<PenItem>(P_PEN);
    pen->setProperty(PenItem::P_COLOR, source_pen->property<QColor>(PenItem::P_COLOR));
    pen->setProperty(PenItem::P_STYLE, source_pen->property<ComboProperty>(PenItem::P_STYLE));
    pen->setProperty(PenItem::P_WIDTH, source_pen->property<int>(PenItem::P_WIDTH));
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

std::vector<double> GraphItem::binErrors() const
{
    return dataItem() ? dataItem()->binErrors() : std::vector<double>();
}

//! Returns color name in #RRGGBB format.

std::string GraphItem::colorName() const
{
    return penItem()->colorName();
}

//! Sets named color following schema from https://www.w3.org/TR/css-color-3/#svg-color.
//! e.g. "mediumaquamarine"

void GraphItem::setNamedColor(const std::string& named_color)
{
    penItem()->setNamedColor(named_color);
}

PenItem* GraphItem::penItem() const
{
    return item<PenItem>(P_PEN);
}
