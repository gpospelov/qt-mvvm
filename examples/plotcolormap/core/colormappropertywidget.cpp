// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "colormappropertywidget.h"
#include "colormapmodel.h"
#include "itemstreeview.h"
#include "standardviewmodels.h"
#include <QBoxLayout>
#include <QPushButton>

using namespace ModelView;

ColorMapPropertyWidget::ColorMapPropertyWidget(ColorMapModel* model, QWidget* parent)
    : QWidget(parent), m_treeView(new ItemsTreeView), m_model(model)
{
    auto mainLayout = new QVBoxLayout;

    mainLayout->addWidget(m_treeView);

    setLayout(mainLayout);
    setModel(model);
}

void ColorMapPropertyWidget::setModel(ColorMapModel* model)
{
    if (!model)
        return;

    m_model = model;

    m_treeView->setViewModel(Utils::CreateDefaultViewModel(model));
}
