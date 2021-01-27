// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/viewmodel/viewmodeldelegate.h"

#include "google_test.h"
#include "widgetbasedtest.h"
#include "mvvm/editors/customeditor.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/standarditems/vectoritem.h"
#include "mvvm/viewmodel/defaultviewmodel.h"
#include <QDataWidgetMapper>
#include <QStyleOptionViewItem>

using namespace ModelView;

//! Tests of ViewModelDelegate class.

class ViewModelDelegateTest : public WidgetBasedTest {
public:
    struct TestData {
        SessionModel model{};
        DefaultViewModel view_model;
        ViewModelDelegate delegate;
        QDataWidgetMapper mapper;

        TestData() : view_model(&model)
        {
            mapper.setModel(&view_model);
            mapper.setItemDelegate(&delegate);
        }

        std::unique_ptr<CustomEditor> create_editor(const QModelIndex& index)
        {
            return std::unique_ptr<CustomEditor>(dynamic_cast<CustomEditor*>(
                delegate.createEditor(nullptr, QStyleOptionViewItem(), index)));
        }

        void map_to_index(QWidget* widget, const QModelIndex& index)
        {
            mapper.setRootIndex(index.parent());
            mapper.setCurrentModelIndex(index.sibling(index.row(), 0));
            mapper.addMapping(widget, 1);
        }
    };

    std::unique_ptr<TestData> test_data() { return std::make_unique<TestData>(); }
};

TEST_F(ViewModelDelegateTest, createEditor)
{
    TestData test_data;
    test_data.model.insertItem<VectorItem>();

    auto parent_index = test_data.view_model.index(0, 0);
    auto x_value_index = test_data.view_model.index(0, 1, parent_index);

    EXPECT_TRUE(test_data.create_editor(x_value_index).get() != nullptr);
}

//! Check that ViewModelDelegate can work with widget mapper.

TEST_F(ViewModelDelegateTest, widgetMapper)
{
    TestData test_data;
    auto vector_item = test_data.model.insertItem<VectorItem>();
    auto x_item = vector_item->getItem(VectorItem::P_X);

    // accessing to index list (index of label field and index of data field)
    // of PropertyItem corresponding to x-coordinate.
    auto x_value_index = test_data.view_model.indexOfSessionItem(x_item).at(1);
    auto editor = test_data.create_editor(x_value_index);

    test_data.map_to_index(editor.get(), x_value_index);

    editor->setData(43.0);
    editor->dataChanged(editor->data());
    EXPECT_EQ(x_item->data<double>(), 43.0);
}
