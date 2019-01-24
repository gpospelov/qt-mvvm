// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef VIEWITEMS_H
#define VIEWITEMS_H

#include "viewitem.h"

namespace ModelView
{

class SessionItem;

//! Represents display name of SessionItem in any cell of Qt's trees and tables.

class CORE_EXPORT ViewLabelItem : public ViewItem
{
public:
    explicit ViewLabelItem(SessionItem* item);
};

//! Represents data role of SessionItem in any cell of Qt's trees and tables.

class CORE_EXPORT ViewDataItem : public ViewItem
{
public:
    explicit ViewDataItem(SessionItem* item);
};

} // namespace ModelView

#endif // VIEWITEMS_H
