// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PLOTCOLORMAPCORE_COLORMAPWIDGET_H
#define PLOTCOLORMAPCORE_COLORMAPWIDGET_H

#include <QWidget>

class QBoxLayout;
class QToolBar;
class QAction;

namespace ModelView {
class ColorMapCanvas;
} // namespace ModelView

namespace PlotColorMap {

class ColorMapModel;
class ColorMapPropertyWidget;

//! Shows canvas with plots on the left and property editor on the right.

class ColorMapWidget : public QWidget {
    Q_OBJECT

public:
    explicit ColorMapWidget(ColorMapModel* model = nullptr, QWidget* parent = nullptr);

    void setModel(ColorMapModel* model);

private:
    void initActions();
    QBoxLayout* createLeftLayout();
    QBoxLayout* createRightLayout();

    QToolBar* m_toolBar{nullptr};
    QAction* m_resetViewportAction{nullptr};

    ColorMapPropertyWidget* m_propertyWidget{nullptr};
    ModelView::ColorMapCanvas* m_colorMapCanvas{nullptr};
    ColorMapModel* m_model{nullptr};
};

} // namespace PlotColorMap

#endif // PLOTCOLORMAPCORE_COLORMAPWIDGET_H
