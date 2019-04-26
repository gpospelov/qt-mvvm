// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef SAMPLEWIDGET_H
#define SAMPLEWIDGET_H

#include <QWidget>

class ApplicationModels;
class QBoxLayout;
class MaterialTableWidget;

namespace ModelView
{
class ItemsTreeView;
}

class SampleWidget : public QWidget
{
    Q_OBJECT
public:
    SampleWidget(ApplicationModels* models, QWidget* parent = nullptr);

private:
    QBoxLayout* create_top_layout();
    QBoxLayout* create_bottom_layout();

    ModelView::ItemsTreeView* m_materialTree;
    ModelView::ItemsTreeView* m_sampleTree;
    MaterialTableWidget* m_materialTableWidget;

    ApplicationModels* m_models;
};

#endif // SAMPLEWIDGET_H
