// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef DESIGNERHELPER_H
#define DESIGNERHELPER_H

#include <QColor>
#include <QGradient>
#include <QGraphicsItem>
#include <QRect>
#include <complex>

//! collection of static methods with SampleDesigner geometry settings
class DesignerHelper
{
public:

    enum EWidgetTypes {
        NODE_EDITOR_PORT = QGraphicsItem::UserType+1,
        NODE_EDITOR_CONNECTION,
        MULTILAYER,
        LAYER,
        PARTICLE_LAYOUT,
        INTERFERENCE_FUNCTION,
        INTERFERENCE_FUNCTION_1D_LATTICE,
        INTERFERENCE_FUNCTION_2D_LATTICE,
        INTERFERENCE_FUNCTION_2D_PARA,
        INTERFERENCE_FUNCTION_FINITE_2D_LATTICE,
        INTERFERENCE_FUNCTION_HARD_DISK,
        INTERFERENCE_FUNCTION_RADIAL_PARA,
        PARTICLE,
        TRANSFORMATION,
    };

    static int getDefaultLayerWidth() { return m_default_layer_width; }
    static int getDefaultLayerHeight() { return m_default_layer_height; }
    static QColor getDefaultLayerColor() { return QColor(Qt::lightGray); }

    static int getDefaultMultiLayerWidth() { return m_default_layer_width*1.15; }
    static int getDefaultMultiLayerHeight() { return m_default_layer_height; }
    static QRectF getDefaultMultiLayerRect();

    static int getDefaultParticleLayoutWidth() { return m_default_layer_height*3.5; }
    static int getDefaultParticleLayoutHeight() { return m_default_layer_height*4.5; }

    static int getDefaultInterferenceFunctionWidth() { return m_default_layer_height*4.5; }
    static int getDefaultInterferenceFunctionHeight() { return m_default_layer_height*4; }

    static int getDefaultParticleWidth() { return m_default_layer_height*3.5; }
    static int getDefaultParticleHeight() { return m_default_layer_height*4; }
    static QColor getDefaultParticleColor() { return QColor(210, 223, 237); }

    static int getDefaultTransformationWidth() { return m_default_layer_height*4; }
    static int getDefaultTransformationHeight() { return m_default_layer_height*2; }
    static QColor getDefaultTransformationColor() { return QColor(145, 50, 220); }

    static int getDefaultMaterialWidth() { return m_default_layer_height*1.2; }
    static int getDefaultMaterialHeight() { return m_default_layer_height*1.2; }
    static QColor getDefaultMaterialColor() { return QColor(qrand() % 256, qrand() % 256, qrand() % 256); }

    static QGradient getLayerGradient(const QColor &color, const QRectF &rect);
    static QGradient getDecorationGradient(const QColor &color, const QRectF &rect);

    static QPixmap getSceneBackground();
    static QPixmap getPixmapLayer();
    static QPixmap getPixmapMultiLayer();
    static QPixmap getPixmapParticleLayout();
    static QPixmap getPixmapInterferenceFunction();
    static QPixmap getPixmapParticle();

    static QColor getRandomColor() { return QColor(qrand() % 256, qrand() % 256, qrand() % 256); }

    //! sort graphics item according they y-coordinate
    static bool sort_layers(QGraphicsItem* left, QGraphicsItem *right) {
        return left->y() < right->y();
    }

    //! returns default bounding rectangle for given IView name
    static QRectF getDefaultBoundingRect(const std::string& name);

    //! returns default color for IView with given name
    static QColor getDefaultColor(const std::string& name);

    //! returns Mime pixmap for givew IView name
    static QPixmap getMimePixmap(const std::string& name);

    //! returns system dependent font size
    static int getHeaderFontSize();
    static int getSectionFontSize();
    static int getLabelFontSize();
    static int getPortFontSize();
    static int getPythonEditorFontSize();

    static void setZoomLevel(double value);

private:
    static int m_default_layer_height;
    static int m_default_layer_width;
    static double m_current_zoom_level;
};

using complex_t = std::complex<double>;
Q_DECLARE_METATYPE(complex_t)

#endif // DESIGNERHELPER_H
