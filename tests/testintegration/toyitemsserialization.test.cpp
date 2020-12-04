// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "toyitems.h"
#include "toymodel.h"
#include <QJsonObject>
#include <mvvm/serialization/jsonmodelconverter.h>

using namespace ModelView;

//! Testing serialization of ToyItems using json converters.

class ToyItemsSerializationTest : public ::testing::Test
{
public:
    //! Returns copy of model obtrained via json serialization.
    std::unique_ptr<ToyItems::SampleModel> createCopy(const ToyItems::SampleModel& model)
    {
        auto result = std::make_unique<ToyItems::SampleModel>();
        JsonModelConverter converter;
        QJsonObject object = converter.to_json(model);
        converter.from_json(object, *result);
        return result;
    }

    ~ToyItemsSerializationTest();
};

ToyItemsSerializationTest::~ToyItemsSerializationTest() = default;

//! Checking ShapeGroupItem in a model.
//! Serialization/deserelization should give an item identical to original.

TEST_F(ToyItemsSerializationTest, defaultShapeGroupItemInModel)
{
    ToyItems::SampleModel model;
    auto group = model.insertItem<ToyItems::ShapeGroupItem>();

    auto modelCopy = createCopy(model);
    auto groupCopy = modelCopy->topItem<ToyItems::ShapeGroupItem>();

    EXPECT_EQ(group->currentIndex(), groupCopy->currentIndex());
    EXPECT_EQ(group->currentItem()->modelType(), groupCopy->currentItem()->modelType());
}
