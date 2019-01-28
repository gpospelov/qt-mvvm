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

class CORE_EXPORT ViewEmptyItem : public ViewItem
{
public:
    explicit ViewEmptyItem();
    int type() const override;

    QVariant data(int role) const override;

    ViewEmptyItem* clone() const override;
};


//! Represents display name of SessionItem in any cell of Qt's trees and tables.

class CORE_EXPORT ViewLabelItem : public ViewItem
{
public:
    explicit ViewLabelItem(SessionItem* item);
    int type() const override;
};

//! Represents data role of SessionItem in any cell of Qt's trees and tables.

class CORE_EXPORT ViewDataItem : public ViewItem
{
public:
    explicit ViewDataItem(SessionItem* item);
    int type() const override;
};

} // namespace ModelView

#endif // VIEWITEMS_H
