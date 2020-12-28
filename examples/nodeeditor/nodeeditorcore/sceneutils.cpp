// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sceneutils.h"
#include <QLinearGradient>

namespace NodeEditor {

QGradient CreateViewGradient(const QColor& color, const QRectF& rect)
{
    QLinearGradient result(rect.x() + rect.width() / 2, rect.y(), rect.x() + rect.width() / 2,
                           rect.y() + rect.height());
    result.setColorAt(0, color);
    result.setColorAt(0.5, color.lighter(150));
    result.setColorAt(1, color);
    return result;
}

} // namespace NodeEditor
