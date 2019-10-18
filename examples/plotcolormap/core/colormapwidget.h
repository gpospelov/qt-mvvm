// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef COLORMAPWIDGET_H
#define COLORMAPWIDGET_H

#include <QWidget>
#include <memory>

class QBoxLayout;
class ColorMapModel;
class ColorMapPropertyWidget;
class QToolBar;
class QAction;

namespace ModelView
{
class ItemsTreeView;
class ColorMapCanvas;
} // namespace ModelView

/*!
@class ColorMapWidget
@brief Shows canvas with plots on the left and property editor on the right.
*/

class ColorMapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorMapWidget(ColorMapModel* model = nullptr, QWidget* parent = nullptr);
    ~ColorMapWidget();

    void setModel(ColorMapModel* model);

private:
    void init_actions();

    QBoxLayout* create_left_layout();
    QBoxLayout* create_right_layout();

    QToolBar* m_toolBar;
    QAction* m_resetViewportAction;
    QAction* m_addPlotAction;
    QAction* m_removePlotAction;

    ColorMapPropertyWidget* m_propertyWidget;
    ModelView::ColorMapCanvas* m_colorMapCanvas;
    ColorMapModel* m_model;
};

#endif // COLORMAPWIDGET_H
