// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef TESTWIDGET3_H
#define TESTWIDGET3_H

#include <QWidget>
#include <memory>

namespace ModelView
{
class SessionItem;
class DefaultViewModel;
class PropertyViewModel;
class ViewModelDelegate;
} // namespace ModelView

namespace ToyItems
{
class SampleModel;
}

class QTreeView;
class QStandardItemModel;
class QPoint;
class QUndoView;
class QBoxLayout;
class QItemSelection;

//! Playground to test basics of ViewModel.

class TestWidget3 : public QWidget
{
    Q_OBJECT
public:
    TestWidget3(QWidget* parent = nullptr);
    ~TestWidget3();

private slots:
    void onContextMenuRequest(const QPoint& point);
    void onDefaultViewSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

private:
    void init_session_model();
    void update_json();
    void init_default_view();
    void init_subset_view();
    ModelView::SessionItem* item_from_view(QTreeView* view, const QPoint& point);

    QBoxLayout* create_top_layout();
    QBoxLayout* create_left_layout();
    QBoxLayout* create_middle_layout();
    QBoxLayout* create_right_layout();

    QTreeView* m_defaultView;
    QTreeView* m_topItemView;
    QTreeView* m_subsetTreeView;
    QTreeView* m_propertyView;
    QUndoView* m_undoView;
    ModelView::DefaultViewModel* m_viewModel;
    ModelView::DefaultViewModel* m_subsetViewModel;
    ModelView::DefaultViewModel* m_propertyViewModel;
    std::unique_ptr<ToyItems::SampleModel> m_sessionModel;
    std::unique_ptr<ModelView::ViewModelDelegate> m_delegate;
};

#endif // TESTWIDGET3_H
