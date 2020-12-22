// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_VIEWITEM_H
#define MVVM_VIEWMODEL_VIEWITEM_H

#include "mvvm/core/variant.h"
#include "mvvm/viewmodel_export.h"
#include <memory>
#include <vector>

namespace ModelView {

class SessionItem;

//! Represents the view of SessionItem's data in a single cell of ViewModel.

class MVVM_VIEWMODEL_EXPORT ViewItem {
public:
    virtual ~ViewItem();

    int rowCount() const;

    int columnCount() const;

    void appendRow(std::vector<std::unique_ptr<ViewItem>> items);

    void insertRow(int row, std::vector<std::unique_ptr<ViewItem>> items);

    void removeRow(int row);

    void clear();

    ViewItem* parent() const;

    ViewItem* child(int row, int column) const;

    SessionItem* item() const;

    int item_role() const;

    int row() const;

    int column() const;

    virtual QVariant data(int qt_role) const;

    virtual bool setData(const QVariant& value, int qt_role);

    virtual Qt::ItemFlags flags() const;

    std::vector<ViewItem*> children() const;

protected:
    ViewItem(SessionItem* item, int role);
    void setParent(ViewItem* parent);

private:
    struct ViewItemImpl;
    std::unique_ptr<ViewItemImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_VIEWITEM_H
