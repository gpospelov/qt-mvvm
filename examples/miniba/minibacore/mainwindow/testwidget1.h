// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef TESTWIDGET1_H
#define TESTWIDGET1_H

#include <QWidget>

class ApplicationModels;
class QBoxLayout;

namespace ModelView
{
class ItemsTreeView;
}

class TestWidget1 : public QWidget
{
    Q_OBJECT
public:
    TestWidget1(ApplicationModels* models, QWidget* parent = nullptr);

private:
    QBoxLayout* create_top_layout();
    QBoxLayout* create_bottom_layout();

    ModelView::ItemsTreeView* m_materialTree;
    ModelView::ItemsTreeView* m_sampleTree;

    ApplicationModels* m_models;
};

#endif // TESTWIDGET1_H
