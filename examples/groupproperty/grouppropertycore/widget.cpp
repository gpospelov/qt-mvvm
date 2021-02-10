// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "widget.h"
#include "mvvm/widgets/allitemstreeview.h"
#include "mvvm/widgets/propertytreeview.h"
#include <QHBoxLayout>

namespace GroupProperty {

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , m_treeView(new ModelView::AllItemsTreeView(&m_model))
    , m_propertyEditor(new ModelView::PropertyTreeView)
{
    auto layout = new QHBoxLayout(this);
    layout->addWidget(m_treeView);
    layout->addWidget(m_propertyEditor);

    // populate the model with single ParticleItem
    auto particleItem = m_model.insertItem<ParticleItem>();

    // and make property editor displaying this item
    m_propertyEditor->setItem(particleItem);
}

} // namespace GroupProperty
