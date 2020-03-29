// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "materialprofile.h"

//! Tests utility functions from MaterialProfile namespace.

class MaterialProfileTest : public ::testing::Test
{
public:
    ~MaterialProfileTest();
};

MaterialProfileTest::~MaterialProfileTest() = default;

TEST_F(MaterialProfileTest, GenerateZValues)
{
    auto values = MaterialProfile::GenerateZValues(0, -2.0, 4.0);
    EXPECT_EQ(values.size(), 0);

    values = MaterialProfile::GenerateZValues(1, -2.0, 4.0);
    EXPECT_EQ(values, std::vector<double>{-2.0});

    values = MaterialProfile::GenerateZValues(2, -2.0, 4.0);
    EXPECT_EQ(values, (std::vector<double>{-2.0, 4.0}));

    values = MaterialProfile::GenerateZValues(3, -2.0, 4.0);
    EXPECT_EQ(values, (std::vector<double>{-2.0, 1.0, 4.0}));

    values = MaterialProfile::GenerateZValues(3, -15.0, 5.0);
    EXPECT_EQ(values, (std::vector<double>{-15.0, -5.0, 5.0}));
}

TEST_F(MaterialProfileTest, DefaultMaterialProfileLimits)
{
    Slice air{{0.0, 0.0}, 0.0, 0.0};
    Slice substrate{{2e-06, 0.0}, 0.0, 0.0};
    multislice_t multislice = {air, substrate};

    auto [xmin, xmax] = MaterialProfile::DefaultMaterialProfileLimits(multislice);
    EXPECT_EQ(xmin, -10.0);
    EXPECT_EQ(xmax, 10.0);
}

TEST_F(MaterialProfileTest, TwoLayersProfile)
{
    Slice air{{0.0, 0.0}, 0.0, 0.0};
    Slice substrate{{2e-06, 0.0}, 0.0, 0.0};
    multislice_t multislice = {air, substrate};

    auto values = MaterialProfile::CalculateProfile(multislice, 2, -10.0, 10.0);
    ASSERT_EQ(values.size(), 2);
    EXPECT_DOUBLE_EQ(values[0].real(), substrate.material.real());
    EXPECT_DOUBLE_EQ(values[1].real(), air.material.real());
}

TEST_F(MaterialProfileTest, ThreeLayersProfile)
{
    Slice air{{0.0, 0.0}, 0.0, 0.0};
    Slice ni{{9e-06, 0.0}, 10.0, 0.0};
    Slice substrate{{2e-06, 0.0}, 0.0, 0.0};
    multislice_t multislice = {air, ni, substrate};

    auto values = MaterialProfile::CalculateProfile(multislice, 3, -15.0, 5.0);
    ASSERT_EQ(values.size(), 3);
    EXPECT_DOUBLE_EQ(values[0].real(), substrate.material.real());
    EXPECT_DOUBLE_EQ(values[1].real(), ni.material.real());
    EXPECT_DOUBLE_EQ(values[2].real(), air.material.real());
}
