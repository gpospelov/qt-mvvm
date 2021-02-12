// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PLOTCOLORMAPCORE_COLORMAPPROPERTYWIDGET_H
#define PLOTCOLORMAPCORE_COLORMAPPROPERTYWIDGET_H

#include <QWidget>
#include <memory>

class QBoxLayout;
class QBoxLayout;
class QSlider;

namespace ModelView {
class ItemsTreeView;
} // namespace ModelView

namespace PlotColorMap {

class ColorMapModel;

//! Shows model content in standard tree view.

class ColorMapPropertyWidget : public QWidget {
    Q_OBJECT

public:
    explicit ColorMapPropertyWidget(ColorMapModel* model = nullptr, QWidget* parent = nullptr);

    void setModel(ColorMapModel* model);

private:
    void setupSlider();
    QSlider* m_slider{nullptr};
    ModelView::ItemsTreeView* m_tree_view{nullptr};
    ColorMapModel* m_model{nullptr};
};

} // namespace PlotColorMap

#endif // PLOTCOLORMAPCORE_COLORMAPPROPERTYWIDGET_H
