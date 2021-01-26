// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_CUSTOMPLOTPROXYWIDGET_H
#define MVVM_PLOTTING_CUSTOMPLOTPROXYWIDGET_H

#include "mvvm/view_export.h"
#include <QGraphicsProxyWidget>

class QWidget;

namespace ModelView {

//! Custom proxy widget to embed color map in graphics scene.

class MVVM_VIEW_EXPORT CustomPlotProxyWidget : public QGraphicsProxyWidget {
    Q_OBJECT

public:
    CustomPlotProxyWidget(QWidget* colormap);

    bool eventFilter(QObject* object, QEvent* event);

    void setBlockSignalsToProxy(bool value);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void wheelEvent(QGraphicsSceneWheelEvent* event);

private:
    bool block_signals_to_proxy{false};
};

} // namespace ModelView

#endif // MVVM_PLOTTING_CUSTOMPLOTPROXYWIDGET_H
