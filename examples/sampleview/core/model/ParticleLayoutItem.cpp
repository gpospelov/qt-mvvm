// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "ParticleLayoutItem.h"
#include "item_constants.h"
#include <mvvm/model/taginfo.h>

using namespace ModelView;

const std::string ParticleLayoutItem::T_INTERFERENCE = "Interference Tag";

ParticleLayoutItem::ParticleLayoutItem()
    : LocatedItem(::Constants::ParticleLayoutType)
{
    registerTag(TagInfo(T_INTERFERENCE, 0, 1, {::Constants::InterferenceFunctionType}));
    setDefaultTag(T_INTERFERENCE);
}

ParticleLayoutItem::~ParticleLayoutItem() = default;
