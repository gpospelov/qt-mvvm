// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "widgetbasedtest.h"
#include <mvvm/editors/booleditor.h>
#include <mvvm/editors/coloreditor.h>
#include <mvvm/editors/combopropertyeditor.h>
#include <mvvm/editors/defaulteditorfactory.h>
#include <mvvm/editors/externalpropertyeditor.h>
#include <mvvm/editors/integereditor.h>
#include <mvvm/editors/scientificdoubleeditor.h>
#include <mvvm/editors/scientificspinboxeditor.h>
#include <mvvm/model/comboproperty.h>
#include <mvvm/model/externalproperty.h>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/utils/reallimits.h>
#include <mvvm/viewmodel/defaultviewmodel.h>

using namespace ModelView;

class DefaultEditorFactoryTest : public WidgetBasedTest
{
public:
    DefaultEditorFactoryTest() : m_factory(std::make_unique<DefaultEditorFactory>()) {}
    ~DefaultEditorFactoryTest();

    //! Helper function to build temporary model and create editor for cell.
    std::unique_ptr<CustomEditor> createEditor(const QVariant& variant)
    {
        // populating model with data
        SessionModel model;
        auto propertyItem = model.insertItem<PropertyItem>();
        propertyItem->setData(variant);

        // create view model and use index of data cell to create an editor
        DefaultViewModel viewModel(&model);
        return m_factory->createEditor(viewModel.index(0, 1));
    }

protected:
    std::unique_ptr<DefaultEditorFactory> m_factory;
};

DefaultEditorFactoryTest::~DefaultEditorFactoryTest() = default;

//! Tests editor creation on bool property.

TEST_F(DefaultEditorFactoryTest, boolProperty)
{
    auto editor = createEditor(QVariant::fromValue(true));
    EXPECT_TRUE(dynamic_cast<BoolEditor*>(editor.get()));
}

//! Tests editor creation on integer property.

TEST_F(DefaultEditorFactoryTest, integerProperty)
{
    auto editor = createEditor(QVariant::fromValue(42));
    EXPECT_TRUE(dynamic_cast<IntegerEditor*>(editor.get()));
}

//! Tests editor creation on double property.

TEST_F(DefaultEditorFactoryTest, doubleProperty)
{
    auto editor = createEditor(QVariant::fromValue(42.42));
    EXPECT_TRUE(dynamic_cast<ScientificSpinBoxEditor*>(editor.get()));
}

//! Tests editor creation on color property.

TEST_F(DefaultEditorFactoryTest, colorProperty)
{
    auto editor = createEditor(QVariant::fromValue(QColor(Qt::green)));
    EXPECT_TRUE(dynamic_cast<ColorEditor*>(editor.get()));
}

//! Tests editor creation on combo property.

TEST_F(DefaultEditorFactoryTest, comboProperty)
{
    auto editor = createEditor(QVariant::fromValue(ComboProperty()));
    EXPECT_TRUE(dynamic_cast<ComboPropertyEditor*>(editor.get()));
}

//! Tests editor creation on combo property.

TEST_F(DefaultEditorFactoryTest, externalProperty)
{
    auto editor = createEditor(QVariant::fromValue(ExternalProperty()));
    EXPECT_TRUE(dynamic_cast<ExternalPropertyEditor*>(editor.get()));
}

//! Tests editor creation on some unsupported property.

TEST_F(DefaultEditorFactoryTest, unsupportedProperty)
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
