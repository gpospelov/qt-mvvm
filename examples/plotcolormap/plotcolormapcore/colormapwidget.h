// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef COLORMAPWIDGET_H
#define COLORMAPWIDGET_H

#include <QWidget>

class QBoxLayout;
class QToolBar;
class QAction;

namespace ModelView
{
class ItemsTreeView;
class ColorMapCanvas;
} // namespace ModelView

namespace PlotColorMap
{

class ColorMapModel;
class ColorMapPropertyWidget;

//! Shows canvas with plots on the left and property editor on the right.

class ColorMapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorMapWidget(ColorMapModel* model = nullptr, QWidget* parent = nullptr);

    void setModel(ColorMapModel* model);

private:
    void init_actions();

    QBoxLayout* create_left_layout();
    QBoxLayout* create_right_layout();

    QToolBar* m_toolBar;
    QAction* m_resetViewportAction;

    ColorMapPropertyWidget* m_propertyWidget;
    ModelView::ColorMapCanvas* m_colorMapCanvas;
    ColorMapModel* m_model;
};

} // namespace PlotColorMap

#endif // COLORMAPWIDGET_H
