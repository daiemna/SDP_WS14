#include "GenICam.h"
#include "gtest/gtest.h"

const std::string kDeviceVendorName = "STEMMER IMAGING GmbH";
const std::string kDeviceModelName = "FGI-HD";
const std::string kDeviceID = "4-1326-0801";
TEST(GetStringFeatureTest, PositiveTest) {
    Cvb::Camera camera("%CVB%/drivers/GenICam.vin");

    // get GenICam access
    Cvb::GenICam genICam(camera);

   EXPECT_EQ(0, kDeviceVendorName.compare(genICam.getStringFeature("DeviceVendorName")));
   EXPECT_EQ(0, kDeviceModelName.compare( genICam.getStringFeature("DeviceModelName")));

   EXPECT_EQ(0, kDeviceID.compare( genICam.getStringFeature("DeviceID")));

}

