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

#include <mvvm/core/export.h>
#include <memory>
#include <QWidget>

namespace ModelView
{

class SessionItem;

/*!
@class PropertyFlatView
@brief Widget holding grid layout with editors and intended for displaying all properties of given
SessionItem.
*/

class CORE_EXPORT PropertyFlatView : public QWidget
{
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
