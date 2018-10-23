#include <gtest/gtest.h>
#include "comparators.h"
#include "TestSessionItem.h"
#include "TestSessionModel.h"
#include "TestPath.h"
#include "TestUndoRedo.h"
#include "TestItemPool.h"
#include "TestItemManager.h"
#include "TestFileUtils.h"
#include "TestItemUtils.h"
#include "TestJsonModel.h"
#include "TestSessionItemData.h"
#include "TestJsonVariant.h"
#include "TestJsonItemData.h"
#include "TestSessionItemTags.h"
#include <string>

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    Comparators::registerComparators();

    // run all google tests
    return RUN_ALL_TESTS();
}
