// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "modeleditorwidget.h"
#include "containereditorwidget.h"
#include "samplemodel.h"
#include <QHBoxLayout>

using namespace ModelView;

ModelEditorWidget::ModelEditorWidget(SampleModel* model, QWidget* parent)
    : QWidget(parent), m_leftWidget(new ContainerEditorWidget),
      m_rightWidget(new ContainerEditorWidget)
{
    auto mainLayout = new QHBoxLayout();
    mainLayout->setSpacing(10);

    mainLayout->addWidget(m_leftWidget);
    mainLayout->addWidget(m_rightWidget);

    setLayout(mainLayout);
    setModel(model);
}

void ModelEditorWidget::setModel(SampleModel* model)
{
    if (!model)
        return;

    m_leftWidget->setModel(model);
    m_rightWidget->setModel(model);
}
