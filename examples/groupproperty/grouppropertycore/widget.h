// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GROUPPROPERTYCORE_WIDGET_H
#define GROUPPROPERTYCORE_WIDGET_H

#include "items.h"
#include <QWidget>

namespace ModelView {
class AllItemsTreeView;
class PropertyTreeView;
} // namespace ModelView

namespace GroupProperty {

class Model;

//! The widget contains a tree view displaying the model content on the left,
//! and property editor showing the content of a single ParticleItem on the right.

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);

private:
    Model m_model;
    ModelView::AllItemsTreeView* m_treeView{nullptr};
    ModelView::PropertyTreeView* m_propertyEditor{nullptr};
};

} // namespace GroupProperty

#endif // GROUPPROPERTYCORE_WIDGET_H
