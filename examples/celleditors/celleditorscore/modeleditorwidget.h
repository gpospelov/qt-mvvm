// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MODELEDITORWIDGET_H
#define MODELEDITORWIDGET_H

#include <QWidget>
#include <memory>

class QBoxLayout;
class QTreeView;
class QTableView;

namespace ModelView
{
class ViewModel;
class ViewModelDelegate;
} // namespace ModelView

namespace CellEditors
{

class SampleModel;

//! Shows content of the model as vertical tree, horizontal tree and table.

class ModelEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModelEditorWidget(SampleModel* model = nullptr, QWidget* parent = nullptr);
    virtual ~ModelEditorWidget() override;

    void setModel(SampleModel* model);

private:
    QBoxLayout* create_left_layout();
    QBoxLayout* create_right_layout();

    QTreeView* m_verticalTree{nullptr};
    QTreeView* m_horizontalTree{nullptr};
    QTableView* m_tableView{nullptr};

    std::unique_ptr<ModelView::ViewModel> m_verticalViewModel;
    std::unique_ptr<ModelView::ViewModel> m_horizontalViewModel;
    std::unique_ptr<ModelView::ViewModelDelegate> m_delegate;
};

} // namespace CellEditors

#endif // MODELEDITORWIDGET_H
