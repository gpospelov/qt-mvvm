// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MODELEDITORWIDGET_H
#define MODELEDITORWIDGET_H

#include <QWidget>
#include <memory>

class QBoxLayout;
class SampleModel;
class QTreeView;
class QTableView;

namespace ModelView
{
class ItemsTreeView;
class AbstractViewModel;
class ViewModelDelegate;
} // namespace ModelView

/*!
@class ModelEditorWidget
@brief Shows content of the model as vertical tree, horizontal tree and table.
*/

class ModelEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModelEditorWidget(SampleModel* model = nullptr, QWidget* parent = nullptr);
    ~ModelEditorWidget();

    void setModel(SampleModel* model);

private:
    QBoxLayout* create_left_layout();
    QBoxLayout* create_right_layout();

    QTreeView* m_verticalTree;
    QTreeView* m_horizontalTree;
    QTableView* m_tableView;

    std::unique_ptr<ModelView::AbstractViewModel> m_verticalViewModel;
    std::unique_ptr<ModelView::AbstractViewModel> m_horizontalViewModel;
    std::unique_ptr<ModelView::ViewModelDelegate> m_delegate;
};

#endif // MODELEDITORWIDGET_H
