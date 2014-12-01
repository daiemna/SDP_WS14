#include "../../src/Camera.h"
#include "gtest/gtest.h"

TEST(CameraTest, NonTriggeredAcquisition) {

    //TODO move this to start of common for all
    Cvb::Camera camera("%CVB%/drivers/GenICam.vin");

    // start non Triggered acquistion
    EXPECT_TRUE(camera.startAcquisition());

    //stop non Triggered acquisition
    EXPECT_TRUE(camera.startAcquisition());
}


