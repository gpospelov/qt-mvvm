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
class SessionModel;
class PropertyEditor;
class ItemsTreeView;
} // namespace ModelView

class QTreeView;
class QUndoView;
class QBoxLayout;

//! Playground to test basics of ViewModel.

class TestWidget : public QWidget
{
    Q_OBJECT
public:
    TestWidget(ModelView::SessionModel* model, QWidget* parent = nullptr);
    ~TestWidget();

private slots:
    void onContextMenuRequest(const QPoint& point);

private:
    ModelView::SessionItem* item_from_view(QTreeView* view, const QPoint& point);

    QBoxLayout* create_top_layout();
    QBoxLayout* create_left_layout();
    QBoxLayout* create_middle_layout();
    QBoxLayout* create_right_layout();

    void init_default_view();
    void init_topitems_view();
    void init_subset_view();

    ModelView::ItemsTreeView* m_defaultTreeView;
    ModelView::ItemsTreeView* m_topItemView;
    ModelView::ItemsTreeView* m_subsetTreeView;
    QUndoView* m_undoView;
    ModelView::PropertyEditor* m_propertyEditor;
    ModelView::SessionModel* m_sessionModel;
};

#endif // TESTWIDGET3_H
