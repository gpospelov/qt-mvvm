// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef GRAPHPROPERTYWIDGET_H
#define GRAPHPROPERTYWIDGET_H

#include <QWidget>
#include <memory>

class QBoxLayout;
class GraphModel;
class QBoxLayout;

namespace ModelView
{
class ItemsTreeView;
} // namespace ModelView

/*!
@class GraphPropertyWidget
@brief Shows model content in standard tree view.
*/

class GraphPropertyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphPropertyWidget(GraphModel* model = nullptr, QWidget* parent = nullptr);

    void setModel(GraphModel* model);

private slots:
    void onRunMeasurement();

private:
    QBoxLayout* create_button_layout();
    ModelView::ItemsTreeView* m_treeView;
};

#endif // GRAPHPROPERTYWIDGET_H
