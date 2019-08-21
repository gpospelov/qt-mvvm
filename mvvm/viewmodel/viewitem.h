// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_VIEWITEM_H
#define MVVM_VIEWITEM_H

#include "mvvm_export.h"
#include <QStandardItem>

namespace ModelView
{

class SessionItem;

//! Represents the view of SessionItem's data in single cell of Qt table/tree.
//! Act as QStandardItem which stores SessionItem inside.
//!
//! In principle, it is intended to show SessionItem's data role, but it can be used for
//! any role SessionItem can carry on board.

class CORE_EXPORT ViewItem : public QStandardItem
{
public:
    ~ViewItem() override;

    QVariant data(int role) const override;

    void setData(const QVariant& value, int role) override;

    SessionItem* item();

    ViewItem* clone() const override;

    int item_role() const;

protected:
    ViewItem(SessionItem* item, int item_role);

    SessionItem* m_item;
    int m_item_role; // one of roles defined in ItemDataRole
};

} // namespace ModelView

#endif // MVVM_VIEWITEM_H
