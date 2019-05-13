// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MULTILAYERITEM_H
#define MULTILAYERITEM_H

#include "mvvm_global.h"
#include "compounditem.h"

class CORE_EXPORT MultiLayerItem : public ModelView::CompoundItem
{
public:
    static const std::string T_LAYERS;
    static const std::string P_NREPETITIONS;
    MultiLayerItem();
};

#endif // MULTILAYERITEM_H

