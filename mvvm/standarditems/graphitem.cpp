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
#include <QColor>

using namespace ModelView;

GraphItem::GraphItem() : CompoundItem(Constants::GraphItemType)
{
    addProperty<LinkedItem>(P_LINK)->setDisplayName("Link");
    addProperty(P_COLOR, QColor(Qt::black))->setDisplayName("Color");
}
