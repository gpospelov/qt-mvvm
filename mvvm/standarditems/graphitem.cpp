// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "graphitem.h"
#include "linkeditem.h"
#include "plotitems.h"
#include "data1ditem.h"
#include "itemmapper.h"
#include <QColor>

using namespace ModelView;

GraphItem::GraphItem() : CompoundItem(Constants::GraphItemType)
{
    addProperty<LinkedItem>(P_LINK)->setDisplayName("Link");
    addProperty(P_COLOR, QColor(Qt::black))->setDisplayName("Color");
    addProperty<TextItem>(P_GRAPH_TITLE)->setDisplayName("Graph title");
}

void GraphItem::setDataItem(Data1DItem* data_item)
{
    auto& link = item<LinkedItem>(P_LINK);
    link.setLink(data_item);
}

//! Returns dataItem linked to given GraphItem. Will work only in the model context
//! because of the nature of LinkedItem.

Data1DItem* GraphItem::dataItem() const
{
    if (!model())
        return nullptr;

    auto& link = item<LinkedItem>(P_LINK);
    return link.linkedItem<Data1DItem>();
}
