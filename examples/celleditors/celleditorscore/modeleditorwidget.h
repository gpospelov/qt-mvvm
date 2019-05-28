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
} // namespace ModelView

//! Shows model content in three widgets.
//! The left widget shows the model as a default tree

class ModelEditorWidget : public QWidget
{
    Q_OBJECT
public:
    ModelEditorWidget(SampleModel* model, QWidget* parent = nullptr);
    ~ModelEditorWidget();

    void setModel(SampleModel* model);

private:
    QBoxLayout* create_left_layout();
    QBoxLayout* create_right_layout();

    ModelView::ItemsTreeView* m_defaultTreeView;
    QTreeView* m_treeView;
    QTableView* m_tableView;
};

#endif // MODELEDITORWIDGET_H
