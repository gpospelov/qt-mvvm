// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "SampleEditorFactory.h"
#include "CustomColorEditor.h"
#include <QColor>
#include <mvvm/widgets/scientificspinbox.h>

std::unique_ptr<QItemEditorFactory> SampleEditorFactory::createStandardSampleEditorFactory()
{
    std::unique_ptr<QItemEditorFactory> factory(new QItemEditorFactory);

    auto scientificSpinBoxCreator = new QStandardItemEditorCreator<ModelView::ScientificSpinBox>();
    auto customColorEditor = new QStandardItemEditorCreator<CustomColorEditor>();

    factory->registerEditor(QVariant::Double, scientificSpinBoxCreator);
    factory->registerEditor(QVariant::Color, customColorEditor);
    return factory;
}
