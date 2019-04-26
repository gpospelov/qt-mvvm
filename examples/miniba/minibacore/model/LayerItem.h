// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef LAYERITEM_H
#define LAYERITEM_H

#include "compounditem.h"

class CORE_EXPORT LayerItem : public ModelView::CompoundItem
{
public:
    static const std::string P_NAME;
    static const std::string P_THICKNESS;
    LayerItem();
};

#endif // LAYERITEM_H

