// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sceneutils.h"
#include "mvvm/widgets/widgetutils.h"
#include <QLinearGradient>
#include <QRectF>

namespace NodeEditor {

QGradient ConnectableViewGradient(const QColor& color, const QRectF& rect)
{
    QLinearGradient result(rect.x() + rect.width() / 2, rect.y(), rect.x() + rect.width() / 2,
                           rect.y() + rect.height());
    result.setColorAt(0, color);
    result.setColorAt(0.5, color.lighter(150));
    result.setColorAt(1, color);
    return result;
}

QRectF ConnectableViewRectangle()
{
    // make size of rectangle depending on 'M'-letter size to address scaling issues
    static QRectF result = QRectF(0, 0, ModelView::Utils::WidthOfLetterM() * 8.2,
                                  ModelView::Utils::HeightOfLetterM() * 8.2);
    return result;
}

} // namespace NodeEditor
