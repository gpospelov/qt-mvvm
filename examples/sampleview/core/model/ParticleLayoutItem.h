// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
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
    static const std::string T_INTERFERENCE;

    ParticleLayoutItem();
    ~ParticleLayoutItem() override;
};

#endif // PARTICLELAYOUTITEM_H
