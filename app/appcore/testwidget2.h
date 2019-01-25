// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef TESTWIDGET2_H
#define TESTWIDGET2_H

#include <QWidget>
#include <memory>

namespace ModelView {
class ViewModel;
}

namespace AppItems {
class SampleModel;
}

class QTreeView;
class QStandardItemModel;

//! Playground to test basics of ViewModel.

class TestWidget2 : public QWidget
{
    Q_OBJECT
public:
    TestWidget2(QWidget* parent = nullptr);
    ~TestWidget2();

private:
    void init_session_model();

    QTreeView* m_treeView;
    ModelView::ViewModel* m_viewModel;
    std::unique_ptr<AppItems::SampleModel> m_sessionModel;
};

#endif // TESTWIDGET2_H
