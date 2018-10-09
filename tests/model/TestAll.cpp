#include <gtest/gtest.h>
#include "TestSessionItem.h"
#include "TestSessionModel.h"
#include "TestPath.h"
#include "TestUndoRedo.h"
#include "TestItemPool.h"
#include "TestItemFactory.h"
#include "TestJsonBasics.h"
#include "TestFileUtils.h"
#include "TestItemUtils.h"
#include "TestModelJson.h"
#include "TestSessionItemData.h"
#include "TestJsonVariant.h"
#include "comparators.h"
#include <string>

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    Comparators::registerComparators();

    // run all google tests
    return RUN_ALL_TESTS();
}
