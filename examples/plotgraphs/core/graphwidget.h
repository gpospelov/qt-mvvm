// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <memory>

class QBoxLayout;
class GraphModel;
class GraphPropertyWidget;

namespace ModelView
{
class ItemsTreeView;
class GraphCanvas;
} // namespace ModelView

/*!
@class GraphWidget
@brief Shows canvas with plots on the left and property editor on the right.
*/

class GraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphWidget(GraphModel* model = nullptr, QWidget* parent = nullptr);
    ~GraphWidget();

    void setModel(GraphModel* model);

private:
    QBoxLayout* create_left_layout();
    QBoxLayout* create_right_layout();
    ModelView::GraphCanvas* m_graphCanvas;
    GraphPropertyWidget* m_propertyWidget;
};

#endif // GRAPHWIDGET_H
