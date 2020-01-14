// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "InterferenceFunctionView.h"
#include "DesignerHelper.h"

namespace
{
constexpr qreal interference_width = IView::basic_width * 0.7;
constexpr qreal interference_height = IView::basic_height * 4.0;
constexpr QRectF interference_shape(-interference_width / 2.0, -interference_height / 2.0,
                                    interference_width, interference_height);
} // namespace

InterferenceFunctionView::InterferenceFunctionView(QGraphicsItem* parent)
    : ConnectableView(parent, DesignerHelper::INTERFERENCE_FUNCTION, interference_shape)
{
    setColor(QColor(255, 236, 139));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
}

void InterferenceFunctionView::addView(IView*)
{
    throw std::runtime_error("Error in InterferenceFunctionView::addView: this view does not imply "
                             "the existance of child views.");
}
