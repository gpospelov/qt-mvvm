// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "DesignerHelper.h"
#include "item_constants.h"
#include <QPainter>
#include <QtGlobal>
#include <cmath>

int DesignerHelper::m_default_layer_height = 30;
int DesignerHelper::m_default_layer_width = 200;
double DesignerHelper::m_current_zoom_level = 1.0;

QGradient DesignerHelper::getLayerGradient(const QColor &color, const QRectF &rect)
{
    QColor c = color;
    c.setAlpha(160);
    QLinearGradient result(rect.topLeft(), rect.bottomRight());
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    result.setColorAt(0, c.darker(150));
    result.setColorAt(0.5, c.lighter(200));
    result.setColorAt(1, c.darker(150));
#else
    result.setColorAt(0, c.dark(150));
    result.setColorAt(0.5, c.light(200));
    result.setColorAt(1, c.dark(150));
#endif
    return result;
}

QGradient DesignerHelper::getDecorationGradient(const QColor &color, const QRectF &rect)
{
    QColor c = color;
    // c.setAlpha(200);
    QLinearGradient result(rect.x() + rect.width() / 2, rect.y(), rect.x() + rect.width() / 2,
                           rect.y() + rect.height());
    result.setColorAt(0, c);
    result.setColorAt(0.5, c.lighter(150));
    result.setColorAt(1, c);
    return result;
}

QPixmap DesignerHelper::getSceneBackground()
{
    const int size = 10;
    QPixmap result(size, size);
    result.fill(QColor(250, 250, 250));
    QPainter tilePainter(&result);
    QColor color(220, 220, 220);
    tilePainter.fillRect(0.0, 0.0, 2, 2, color);
    tilePainter.end();

    return result;
}

QPixmap DesignerHelper::getPixmapLayer()
{
    QRect rect(0, 0, DesignerHelper::getDefaultLayerWidth(),
               DesignerHelper::getDefaultLayerHeight());
    QPixmap pixmap(rect.width() + 1, rect.height() + 1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(DesignerHelper::getLayerGradient(Qt::green, rect));
    painter.drawRect(rect);
    return pixmap;
}

QPixmap DesignerHelper::getPixmapMultiLayer()
{
    QRect rect(0, 0, DesignerHelper::getDefaultMultiLayerWidth(),
               DesignerHelper::getDefaultLayerHeight());
    QPixmap pixmap(rect.width() + 1, rect.height() + 1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(DesignerHelper::getLayerGradient(QColor(75, 157, 249), rect));
    painter.drawRect(rect);
    painter.setPen(Qt::DashLine);
    painter.drawLine(0, DesignerHelper::getDefaultLayerHeight() * 0.3,
                     DesignerHelper::getDefaultMultiLayerWidth(),
                     DesignerHelper::getDefaultLayerHeight() * 0.3);
    painter.drawLine(0, DesignerHelper::getDefaultLayerHeight() * 0.6,
                     DesignerHelper::getDefaultMultiLayerWidth(),
                     DesignerHelper::getDefaultLayerHeight() * 0.6);
    return pixmap;
}

QPixmap DesignerHelper::getPixmapParticleLayout()
{
    QRect rect(0, 0, DesignerHelper::getDefaultParticleLayoutWidth(),
               DesignerHelper::getDefaultParticleLayoutHeight());
    QPixmap pixmap(rect.width() + 1, rect.height() + 1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(DesignerHelper::getDecorationGradient(QColor(135, 206, 50), rect));
    painter.drawRoundedRect(rect, 3, 3);
    return pixmap;
}

QPixmap DesignerHelper::getPixmapInterferenceFunction()
{
    QRect rect(0, 0, DesignerHelper::getDefaultInterferenceFunctionWidth(),
               DesignerHelper::getDefaultInterferenceFunctionHeight());
    QPixmap pixmap(rect.width() + 1, rect.height() + 1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(DesignerHelper::getDecorationGradient(Qt::lightGray, rect));
    painter.drawRoundedRect(rect, 3, 3);
    return pixmap;
}

QPixmap DesignerHelper::getPixmapParticle()
{
    QRect rect(0, 0, DesignerHelper::getDefaultParticleWidth(),
               DesignerHelper::getDefaultParticleHeight());
    QPixmap pixmap(rect.width() + 1, rect.height() + 1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    // painter.setBrush(DesignerHelper::getDecorationGradient(QColor(120, 165, 215), rect));
    painter.setBrush(
        DesignerHelper::getDecorationGradient(DesignerHelper::getDefaultParticleColor(), rect));
    painter.drawRoundedRect(rect, 5, 5);
    return pixmap;
}

QRectF DesignerHelper::getDefaultBoundingRect(const std::string& name)
{
    if (name == Constants::MultiLayerType) {
        return QRectF(0, 0, getDefaultMultiLayerWidth(), getDefaultMultiLayerHeight());
    } else if (name == Constants::LayerType) {
        return QRectF(0, 0, getDefaultLayerWidth(), getDefaultLayerHeight());
    } else {
        return QRectF(0, 0, 50, 50);
    }
}

QColor DesignerHelper::getDefaultColor(const std::string& name)
{
    if (name == Constants::MultiLayerType) {
        // return QColor(Qt::blue);
        return QColor(51, 116, 255);
    } else if (name == Constants::LayerType) {
        // return QColor(Qt::green);
        return QColor(26, 156, 9);
    }
    else if(name == "Transparant red") {
        return QColor(0xFF, 0, 0, 0x80);
    }
    else if(name == "Transparant blue") {
        return QColor(0, 0, 0xFF, 0x80);
    }
    else {
        return QColor(Qt::lightGray);
    }
}

QPixmap DesignerHelper::getMimePixmap(const std::string& name)
{
    QRectF default_rect = getDefaultBoundingRect(name);
    QRectF mime_rect(0, 0, default_rect.width() * m_current_zoom_level,
                     default_rect.height() * m_current_zoom_level);

    QPixmap pixmap(mime_rect.width() + 1, mime_rect.height() + 1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(DesignerHelper::getDecorationGradient(getDefaultColor(name), mime_rect));
    painter.drawRoundedRect(mime_rect, 1, 1);
    return pixmap;
}

int DesignerHelper::getHeaderFontSize()
{
#ifdef Q_OS_MAC
    return 14;
#else
    return 12;
#endif
}

QRectF DesignerHelper::getDefaultMultiLayerRect()
{
    return QRectF(0, 0, DesignerHelper::getDefaultMultiLayerWidth(),
                  DesignerHelper::getDefaultMultiLayerHeight());
}

int DesignerHelper::getSectionFontSize()
{
#ifdef Q_OS_MAC
    return 12;
#else
    return 10;
#endif
}

int DesignerHelper::getLabelFontSize()
{
#ifdef Q_OS_MAC
    return 12;
#else
    return 10;
#endif
}

int DesignerHelper::getPortFontSize()
{
#ifdef Q_OS_MAC
    return 10;
#else
    return 8;
#endif
}

int DesignerHelper::getPythonEditorFontSize()
{
#ifdef Q_OS_MAC
    return 13;
#else
    return 10;
#endif
}

void DesignerHelper::setZoomLevel(double value)
{
    m_current_zoom_level = value;
}
