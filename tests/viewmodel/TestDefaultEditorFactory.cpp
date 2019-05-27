#include "defaultviewmodel.h"
#include "google_test.h"
#include "sessionmodel.h"
#include "defaultviewmodel.h"
#include "defaulteditorfactory.h"
#include "scientificspinboxeditor.h"
#include "scientificdoubleeditor.h"
#include "combopropertyeditor.h"
#include "booleditor.h"
#include "coloreditor.h"
#include "externalpropertyeditor.h"
#include "sessionitem.h"

using namespace ModelView;

class TestDefaultEditorFactory : public ::testing::Test
{
public:
    TestDefaultEditorFactory() : m_factory(std::make_unique<DefaultEditorFactory>()) {}
    ~TestDefaultEditorFactory();

    //! Helper function to build temporary model and create editor for cell.
    std::unique_ptr<CustomEditor> createEditor(const QVariant& variant)
    {
        // populating model with data
        SessionModel model;
        auto propertyItem = model.insertNewItem(Constants::PropertyType);
        propertyItem->setData(variant, ItemDataRole::DATA);

        // create view model and use index of data cell to create an editor
        DefaultViewModel viewModel;
        viewModel.setSessionModel(&model);
        return m_factory->createEditor(viewModel.index(0, 1));
    }

private:
    std::unique_ptr<DefaultEditorFactory> m_factory;
};

TestDefaultEditorFactory::~TestDefaultEditorFactory() = default;

//! Tests editor creation on double property.

TEST_F(TestDefaultEditorFactory, doubleProperty)
{
    auto editor = createEditor(QVariant::fromValue(42.42));
//    EXPECT_TRUE(dynamic_cast<ScientificSpinBoxEditor*>(editor.get()));
}
