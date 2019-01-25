#include "google_test.h"
#include "viewmodel.h"
#include "viewitems.h"
#include "toy_includes.h"
#include <QDebug>

using namespace ModelView;

class TestViewModel : public ::testing::Test
{
public:
    ~TestViewModel();
};

TestViewModel::~TestViewModel() = default;

TEST_F(TestViewModel, initialState)
{
    ViewModel viewModel;
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
}

TEST_F(TestViewModel, fromMultiLayer)
{
    ToyItems::SampleModel model;
    model.insertNewItem(ToyItems::Constants::MultiLayerType);

    ViewModel viewModel;
    viewModel.setSessionModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 1);
}



