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
#include <tuple>

class ILayerView;
class MultiLayerView;

namespace DesignerSceneUtils
{
//! Constructs the line for visual representation of layer interface in a multilayer
QLineF getInterfaceToScene(const MultiLayerView& sample, int row);

//! Finds the multilayer and the row position nearest to the center of the given view
std::tuple<MultiLayerView*, int> nearestMultilayer(const ILayerView& view);
};

#endif // DESIGNERSCENEUTILS_H
