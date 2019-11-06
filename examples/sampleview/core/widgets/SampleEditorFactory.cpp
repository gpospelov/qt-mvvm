#include "SampleEditorFactory.h"
#include "CustomColorEditor.h"
#include <mvvm/widgets/scientificspinbox.h>
#include <QColor>

std::unique_ptr<QItemEditorFactory> SampleEditorFactory::createStandardSampleEditorFactory()
{
    std::unique_ptr<QItemEditorFactory> factory(new QItemEditorFactory);

    auto scientificSpinBoxCreator = new QStandardItemEditorCreator<ModelView::ScientificSpinBox>();
    auto customColorEditor = new QStandardItemEditorCreator<CustomColorEditor>();

    factory->registerEditor(QVariant::Double, scientificSpinBoxCreator);
    factory->registerEditor(QVariant::Color, customColorEditor);
    return factory;
}
