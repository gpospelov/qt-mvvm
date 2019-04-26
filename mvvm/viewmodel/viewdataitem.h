// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVMV_VIEWDATAITEM_H
#define MVVMV_VIEWDATAITEM_H

#include "viewitem.h"

namespace ModelView
{

class SessionItem;

//! Represents data role of SessionItem in any cell of Qt's trees and tables.

class CORE_EXPORT ViewDataItem : public ViewItem
{
public:
    explicit ViewDataItem(SessionItem* item);
    int type() const override;

    QVariant data(int role) const override;
};

} // namespace ModelView

#endif // MVVMV_VIEWDATAITEM_H
