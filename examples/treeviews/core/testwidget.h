// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include <memory>

namespace ModelView
{
class SessionItem;
class SessionModel;
class PropertyEditor;
class ItemsTreeView;
class AllItemsTreeView;
class PropertyTreeView;
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

    void connect_default_view();
    void init_topitems_view();

    ModelView::AllItemsTreeView* m_defaultTreeView;
    ModelView::ItemsTreeView* m_topItemView;
    ModelView::AllItemsTreeView* m_subsetTreeView;
    QUndoView* m_undoView;
    ModelView::PropertyTreeView* m_propertyEditor;
    ModelView::SessionModel* m_sessionModel;
};

#endif // TESTWIDGET_H
