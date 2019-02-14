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
}

namespace ToyItems
{
class SampleModel;
}

class QTreeView;
class QStandardItemModel;
class QPoint;
class QUndoView;

//! Playground to test basics of ViewModel.

class TestWidget3 : public QWidget
{
    Q_OBJECT
public:
    TestWidget3(QWidget* parent = nullptr);
    ~TestWidget3();

private slots:
    void onContextMenuRequest(const QPoint& point);

private:
    void init_session_model();
    void update_json();
    void init_tree_view(QTreeView* view);
    ModelView::SessionItem* item_from_view(QTreeView* view, const QPoint& point);

    QTreeView* m_treeView;
    QUndoView* m_undoView;
    ModelView::DefaultViewModel* m_viewModel;
    std::unique_ptr<ToyItems::SampleModel> m_sessionModel;
};

#endif // TESTWIDGET3_H
