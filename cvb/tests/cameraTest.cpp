#include "cameraTest.h"

//Tests that the LoadImageFile works
//
TEST_F(iCVCUtilitiesTest, LoadingImage) {

    static const size_t DRIVERPATHSIZE = 256;

    // load the camera
    char driverPath[DRIVERPATHSIZE] = { 0 };
    TranslateFileName("%CVB%/drivers/GenICam.vin", driverPath, DRIVERPATHSIZE);
    IMG hCamera = NULL;
    
//    EXPECT_PRED2(LoadImageFile, driverPath, hCamera);    
    
    EXPECT_TRUE(LoadImageFile (driverPath, hCamera));
}
