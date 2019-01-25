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
    EXPECT_EQ(1, 1);
}
