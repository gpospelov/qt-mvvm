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
#include "comboproperty.h"
#include "sessionitem.h"
#include "externalproperty.h"
#include "reallimits.h"
#include "integereditor.h"

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

protected:
    std::unique_ptr<DefaultEditorFactory> m_factory;
};

TestDefaultEditorFactory::~TestDefaultEditorFactory() = default;

//! Tests editor creation on bool property.

TEST_F(TestDefaultEditorFactory, boolProperty)
{
    auto editor = createEditor(QVariant::fromValue(true));
    EXPECT_TRUE(dynamic_cast<BoolEditor*>(editor.get()));
}

//! Tests editor creation on integer property.

TEST_F(TestDefaultEditorFactory, integerProperty)
{
    auto editor = createEditor(QVariant::fromValue(42));
    EXPECT_TRUE(dynamic_cast<IntegerEditor*>(editor.get()));
}

//! Tests editor creation on double property.

TEST_F(TestDefaultEditorFactory, doubleProperty)
{
    auto editor = createEditor(QVariant::fromValue(42.42));
    EXPECT_TRUE(dynamic_cast<ScientificSpinBoxEditor*>(editor.get()));
}

//! Tests editor creation on color property.

TEST_F(TestDefaultEditorFactory, colorProperty)
{
    auto editor = createEditor(QVariant::fromValue(QColor(Qt::green)));
    EXPECT_TRUE(dynamic_cast<ColorEditor*>(editor.get()));
}

//! Tests editor creation on combo property.

TEST_F(TestDefaultEditorFactory, comboProperty)
{
    auto editor = createEditor(QVariant::fromValue(ComboProperty()));
    EXPECT_TRUE(dynamic_cast<ComboPropertyEditor*>(editor.get()));
}

//! Tests editor creation on combo property.

TEST_F(TestDefaultEditorFactory, externalProperty)
{
    auto editor = createEditor(QVariant::fromValue(ExternalProperty()));
    EXPECT_TRUE(dynamic_cast<ExternalPropertyEditor*>(editor.get()));
}

//! Tests editor creation on some unsupported property.

TEST_F(TestDefaultEditorFactory, unsupportedProperty)
{
    // no dedicated editor for std::string yet
    auto editor = createEditor(QVariant::fromValue(std::string("text")));
    EXPECT_EQ(editor.get(), nullptr);

    // no editor for RealLimits
    editor = createEditor(QVariant::fromValue(RealLimits::limited(1.0, 2.0)));
    EXPECT_EQ(editor.get(), nullptr);

    // no editor for invalid variant
    editor = createEditor(QVariant());
    EXPECT_EQ(editor.get(), nullptr);

    // special case of invalid index
    EXPECT_EQ(m_factory->createEditor(QModelIndex()), nullptr);
}
