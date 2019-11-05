// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include <mvvm/standarditems/colormapitem.h>
#include <mvvm/standarditems/data2ditem.h>
#include <mvvm/standarditems/linkeditem.h>
#include <mvvm/standarditems/plottableitems.h>
#include <QColor>

using namespace ModelView;

ColorMapItem::ColorMapItem() : CompoundItem(Constants::ColorMapItemType)
{
    addProperty<LinkedItem>(P_LINK)->setDisplayName("Link");
    addProperty<TextItem>(P_TITLE)->setDisplayName("Title");
    addProperty(P_GRADIENT, "undefined")->setDisplayName("Gradient");
    addProperty(P_INTERPOLATION, true)->setDisplayName("Interpolation");
}

//! Sets link to the data item.

void ColorMapItem::setDataItem(const Data2DItem* data_item)
{
    item<LinkedItem>(P_LINK)->setLink(data_item);
}

//! Returns data item linked to the given ColorMapItem.

Data2DItem* ColorMapItem::dataItem() const
{
    return item<LinkedItem>(P_LINK)->get<Data2DItem>();
}
