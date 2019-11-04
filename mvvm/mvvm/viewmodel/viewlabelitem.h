// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_VIEWLABELITEM_H
#define MVVM_VIEWLABELITEM_H

#include "viewitem.h"

namespace ModelView
{

class SessionItem;

//! Represents display name of SessionItem in any cell of Qt's trees and tables.

class CORE_EXPORT ViewLabelItem : public ViewItem
{
public:
    explicit ViewLabelItem(SessionItem* item);
    int type() const override;

    QVariant data(int role) const override;
};

} // namespace ModelView

#endif // MVVM_VIEWITEMS_H
