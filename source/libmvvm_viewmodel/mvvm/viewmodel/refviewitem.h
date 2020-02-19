// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_REFVIEWITEM_H
#define MVVM_VIEWMODEL_REFVIEWITEM_H

#include <memory>
#include <mvvm/core/export.h>
#include <vector>
#include <QVariant>

namespace ModelView
{

class SessionItem;

//! Represents the view of SessionItem's data in single cell of ViewModel.

class CORE_EXPORT RefViewItem
{
public:
    virtual ~RefViewItem();

    int rowCount() const;

    int columnCount() const;

    void appendRow(std::vector<std::unique_ptr<RefViewItem>> items);

    void insertRow(int row, std::vector<std::unique_ptr<RefViewItem>> items);

    void removeRow(int row);

    void clear();

    RefViewItem* parent() const;

    RefViewItem* child(int row, int column) const;

    SessionItem* item() const;

    int item_role() const;

    int row() const;

    int column() const;

    QVariant data(int qt_role) const;

    void setData(const QVariant& value, int qt_role);

protected:
    RefViewItem(SessionItem* item, int role);
    void setParent(RefViewItem* parent);

private:
    friend class RefViewModel;
    struct RefViewItemImpl;
    std::unique_ptr<RefViewItemImpl> p_impl;
};

}; // namespace ModelView

#endif // MVVM_VIEWMODEL_REFVIEWITEM_H
