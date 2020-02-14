// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXY_CUSTOMPLOTPROXYWIDGET_H
#define GRAPHICSPROXY_CUSTOMPLOTPROXYWIDGET_H

#include <QGraphicsProxyWidget>

class QWidget;

//! Custom proxy widget to embed color map in graphics scene.

class CustomPlotProxyWidget : public QGraphicsProxyWidget
{
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

#endif //  GRAPHICSPROXY_CUSTOMPLOTPROXYWIDGET_H
