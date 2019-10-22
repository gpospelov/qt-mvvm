// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef DESIGNERSCENEUTILS_H
#define DESIGNERSCENEUTILS_H

#include <QLineF>
#include <QSet>
#include <map>
#include <tuple>

class ILayerView;
class MultiLayerView;
class QGraphicsItem;

namespace ModelView {
class SessionItem;
}

namespace DesignerSceneUtils
{
//! Constructs the line for visual representation of layer interface in a multilayer
QLineF getInterfaceToScene(const MultiLayerView& sample, int row);

//! Finds the multilayer and the row position nearest to the center of the given view
std::tuple<MultiLayerView*, int> nearestMultilayer(const ILayerView& view);

//! Filters out items if their ancestors (parents, grandparents, etc.) are in the input set.
QSet<ModelView::SessionItem*> headItems(const QSet<ModelView::SessionItem*>& items);

//! Creates and returns an equivalence table between _origin_ and _copy_. The return table
//! includes the children of passed arguments. If the second argument is not a full copy of the
//! first one, function behavior is undefined.
std::map<ModelView::SessionItem*, ModelView::SessionItem*>
makeLookupTable(ModelView::SessionItem* origin, ModelView::SessionItem* copy);

//! Appends all the views' children and returns a copy.
QSet<QGraphicsItem*> appendChildren(QList<QGraphicsItem*> views);

//! Filters session items corresponding to some IView instances and returns them.
QList<ModelView::SessionItem*> visibleItems(const std::vector<ModelView::SessionItem*>& items);
QList<ModelView::SessionItem*> visibleItems(const QSet<ModelView::SessionItem*>& items);
};

#endif // DESIGNERSCENEUTILS_H
