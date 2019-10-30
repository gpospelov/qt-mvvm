// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef COLORMAPPROPERTYWIDGET_H
#define COLORMAPPROPERTYWIDGET_H

#include <QWidget>
#include <memory>

class QBoxLayout;
class ColorMapModel;
class QBoxLayout;
class QSlider;

namespace ModelView
{
class ItemsTreeView;
} // namespace ModelView

/*!
@class ColorMapPropertyWidget
@brief Shows model content in standard tree view.
*/

class ColorMapPropertyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorMapPropertyWidget(ColorMapModel* model = nullptr, QWidget* parent = nullptr);

    void setModel(ColorMapModel* model);

private:
    void setup_slider();

    QBoxLayout* create_button_layout();
    QSlider* m_slider;
    ModelView::ItemsTreeView* m_treeView;
    ColorMapModel* m_model;
};

#endif // COLORMAPPROPERTYWIDGET_H
