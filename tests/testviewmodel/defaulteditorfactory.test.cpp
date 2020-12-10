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
#include <QSpinBox>
#include <QStandardItemModel>
#include <limits>
#include <mvvm/editors/booleditor.h>
#include <mvvm/editors/coloreditor.h>
#include <mvvm/editors/combopropertyeditor.h>
#include <mvvm/editors/defaulteditorfactory.h>
#include <mvvm/editors/editor_constants.h>
#include <mvvm/editors/externalpropertyeditor.h>
#include <mvvm/editors/integereditor.h>
#include <mvvm/editors/scientificdoubleeditor.h>
#include <mvvm/editors/scientificspinbox.h>
#include <mvvm/editors/scientificspinboxeditor.h>
#include <mvvm/editors/selectablecomboboxeditor.h>
#include <mvvm/model/comboproperty.h>
#include <mvvm/model/externalproperty.h>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/utils/reallimits.h>
#include <mvvm/viewmodel/defaultviewmodel.h>
#include <mvvm/viewmodel/viewmodeldelegate.h>

using namespace ModelView;

class DefaultEditorFactoryTest : public WidgetBasedTest
{
public:
    DefaultEditorFactoryTest() : m_factory(std::make_unique<DefaultEditorFactory>()) {}
    ~DefaultEditorFactoryTest();

    //! Helper function to build temporary model and create editor for cell.
    std::unique_ptr<CustomEditor> createEditor(const QVariant& variant,
                                               RealLimits limits = RealLimits::limitless(),
                                               const std::string& editor_type = {})
    {
        // populating model with data
        SessionModel model;
        auto propertyItem = model.insertItem<PropertyItem>();
        propertyItem->setData(variant);
        if (limits.hasLowerLimit() || limits.hasUpperLimit())
            propertyItem->setLimits(limits);
        if (!editor_type.empty())
            propertyItem->setEditorType(editor_type);

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

    auto spin_box = editor->findChild<QSpinBox*>();

    ASSERT_TRUE(spin_box != nullptr);
    EXPECT_EQ(spin_box->minimum(), -65536);
    EXPECT_EQ(spin_box->maximum(), 65536);
}

//! Tests editor creation on integer property with limits.

TEST_F(DefaultEditorFactoryTest, integerPropertyWithLimits)
{
    auto editor = createEditor(QVariant::fromValue(42), RealLimits::limited(-1, 1));
    EXPECT_TRUE(dynamic_cast<IntegerEditor*>(editor.get()));

    auto spin_box = editor->findChild<QSpinBox*>();
    ASSERT_TRUE(spin_box != nullptr);
    EXPECT_EQ(spin_box->minimum(), -1);
    EXPECT_EQ(spin_box->maximum(), 1);
}

//! Tests editor creation on double property.

TEST_F(DefaultEditorFactoryTest, doubleProperty)
{
    auto editor = createEditor(QVariant::fromValue(42.42));
    EXPECT_TRUE(dynamic_cast<ScientificSpinBoxEditor*>(editor.get()));

    auto spin_box = editor->findChild<ScientificSpinBox*>();
    ASSERT_TRUE(spin_box != nullptr);
    EXPECT_FLOAT_EQ(spin_box->minimum(), -std::numeric_limits<double>::max());
    EXPECT_FLOAT_EQ(spin_box->maximum(), std::numeric_limits<double>::max());
}

//! Tests editor creation on double property with limits.

TEST_F(DefaultEditorFactoryTest, doublePropertyWithLimits)
{
    auto editor = createEditor(QVariant::fromValue(42.42), RealLimits::limited(41, 43));
    EXPECT_TRUE(dynamic_cast<ScientificSpinBoxEditor*>(editor.get()));

    auto spin_box = editor->findChild<ScientificSpinBox*>();
    ASSERT_TRUE(spin_box != nullptr);
    EXPECT_FLOAT_EQ(spin_box->minimum(), 41);
    EXPECT_FLOAT_EQ(spin_box->maximum(), 43);
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

//! Create test editor using EDITOR role.

TEST_F(DefaultEditorFactoryTest, editorType)
{
    auto editor = createEditor(QVariant::fromValue(ComboProperty()), RealLimits(),
                               Constants::SelectableComboPropertyEditorType);
    EXPECT_TRUE(dynamic_cast<SelectableComboBoxEditor*>(editor.get()));
}

//! Tests editor creation on combo property in QStandardItemModel with our variant.

TEST_F(DefaultEditorFactoryTest, comboPropertyInStandardModel)
{
    QStandardItemModel model;
    auto parent = model.invisibleRootItem();
    QList<QStandardItem*> children{new QStandardItem};
    parent->appendRow(children);

    auto item = model.item(0, 0);
    item->setData(QVariant::fromValue(ComboProperty()), Qt::EditRole);

    auto editor = m_factory->createEditor(model.index(0, 0));
    EXPECT_TRUE(dynamic_cast<ComboPropertyEditor*>(editor.get()));
}
