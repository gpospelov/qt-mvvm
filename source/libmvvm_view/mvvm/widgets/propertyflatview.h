// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_WIDGETS_PROPERTYFLATVIEW_H
#define MVVM_WIDGETS_PROPERTYFLATVIEW_H

#include "mvvm/view_export.h"
#include <QWidget>
#include <memory>

namespace ModelView {

class SessionItem;

//! Widget holding grid layout with editors and intended for displaying all properties of given
//! SessionItem.

class MVVM_VIEW_EXPORT PropertyFlatView : public QWidget {
    Q_OBJECT

public:
    PropertyFlatView(QWidget* parent = nullptr);
    ~PropertyFlatView();

    void setItem(SessionItem* item);

private:
    struct PropertyFlatViewImpl;
    std::unique_ptr<PropertyFlatViewImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_WIDGETS_PROPERTYFLATVIEW_H
