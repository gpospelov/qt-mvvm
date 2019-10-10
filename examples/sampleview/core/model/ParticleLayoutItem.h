// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef PARTICLELAYOUTITEM_H
#define PARTICLELAYOUTITEM_H

#include "LocatedItem.h"

/*!
@class ParticleLayoutItem
@brief Represents particle layout instance in the GUI.
*/

class ParticleLayoutItem : public LocatedItem
{
public:
    ParticleLayoutItem();
    ~ParticleLayoutItem() override;
};

#endif // PARTICLELAYOUTITEM_H
