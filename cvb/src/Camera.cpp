// ---------------------------------------------------------------------------
/// \file Camera.cpp
/// \author S.Kinzler
///
/// \brief Implementation of the \c Camera class.
// ---------------------------------------------------------------------------

#include <sstream>
#include <iCVCDriver.h>
#include <iCVCUtilities.h>
#include "Camera.h"
#include "CvbError.h"

#ifdef __linux__

#include <unistd.h>

void Cvb::this_thread::sleep(unsigned int mseconds)
{
  usleep(mseconds * 1000);
}

#else

#include <Windows.h>

void Cvb::this_thread::sleep(unsigned int mseconds)
{
  Sleep(mseconds);
}

#endif

// Constant initialization
const cvbbool_t Cvb::Camera::SOFTWARE_TRIGGER = true;

// ---------------------------------------------------------------------------
/// \brief Constructor for the Camera object
///
/// \param [in] driver Driver string to be used (e.g. "%CVB%/drivers/GenICam.vin")
/// \throws CvbError thrown if \a driver could not be opened.
// ---------------------------------------------------------------------------
Cvb::Camera::Camera(const std::string &driver)
{
  static const size_t SIZE = 256;
  char driverPath[SIZE] = { 0 };
  cvbbool_t success = TranslateFileName(driver.c_str(), driverPath, SIZE);
  if(!success)
    throw std::runtime_error("Error loading driver. TranslateFileName failed.");

  // load the camera
  IMG hImage = NULL;
  success = LoadImageFile(driverPath, hImage); 
  if(!success)
    throw CvbError("Error loading driver: " + driver, CVC_ERROR(CVC_E_FILEIO));

  // adopt life-time 
  // (load creates life image and we don't need the handle here anymore)
  cvbImage_ = CvbImage(hImage, CvbImage::dontShare);

  // Set Timeout to 2000ms
  SetTimeout(cvbImage_.get(), 2000);
}


// ---------------------------------------------------------------------------
/// \brief Get Number of available cameras 
///
/// \return The number of available cameras.
/// \throws CvbError thrown if an error occurred. 
// ---------------------------------------------------------------------------
cvbval_t Cvb::Camera::getNumCameras() const
{
  // Check if CameraSelect2 Interface is supported
  if(!CanCameraSelect2(cvbImage_.get()))
    throw CvbError("Changing camera port not possible. CameraSelect2 Interface not supported", CVC_ERROR(CVC_E_NOTSUPPORTED));

  // Check if given camPort is within the available camera ports
  cvbval_t numPorts = -1;
  cvbres_t result = CS2GetNumPorts(cvbImage_.get(), numPorts);
  if(result != 0)
    throw CvbError("Changing camera port not possible. Error reading number of available camera ports", result);

  return numPorts;
}

// ---------------------------------------------------------------------------
/// \brief Get current port of this camera
///
/// \return The current port of the camera.
/// \throws CvbError thrown if an error occurred. 
// ---------------------------------------------------------------------------
cvbval_t Cvb::Camera::getPort() const
{
  // Check if CameraSelect2 Interface is supported
  if(!CanCameraSelect2(cvbImage_.get()))
    throw CvbError("Changing camera port not possible. CameraSelect2 Interface not supported", CVC_ERROR(CVC_E_NOTSUPPORTED));

  // Get current camera port
  cvbval_t currentPort = -1;
  cvbres_t result = CS2GetCamPort(cvbImage_.get(),currentPort);
  if(result != 0)
    throw CvbError("Changing camera port not possible. Error reading current camera port", result);

  return currentPort;
}

// ---------------------------------------------------------------------------
/// \brief Change port to the given camera port
///
/// \param [in] camPort Camera port to change to.
/// \throws CvbError thrown if an error occurred while switching the port. 
// ---------------------------------------------------------------------------
void Cvb::Camera::switchCamPort(cvbval_t camPort)
{
  // Check if current port is already the needed camPort
  if(getPort() == camPort)
    return;

  if(camPort >= getNumCameras())
    throw CvbError("Changing camera port not possible. Given port is not available");
  
  // Change the port
  IMG hImgNew = NULL;
  cvbres_t result = CS2SetCamPort(cvbImage_.get(), camPort, 0, hImgNew);
  if(result != 0)
    throw CvbError("Changing camera port not possible. Error calling CS2SetCamPort", result);
  
  // Set the new CvbImage Object to the original. The old image will be released automatically. 
  cvbImage_ = CvbImage(hImgNew, CvbImage::dontShare);
}

// ---------------------------------------------------------------------------
/// \brief Starts the acquisition of the camera.
///
/// \return \b false if an error occurred otherwise \b true.
// ---------------------------------------------------------------------------
cvbbool_t Cvb::Camera::startAcquisition()
{
  // start grab with ring buffer
  cvbres_t result = G2Grab(cvbImage_.get()); 
  return result >= 0;
}


// ---------------------------------------------------------------------------
/// \brief Stops the acquisition of the camera
///
/// \return \b false if an error occurred otherwise \b true.
// ---------------------------------------------------------------------------
cvbbool_t Cvb::Camera::stopAcquisition()
{
  // stop the grab 
  //               (kill = true : stop acquisition immediately without waiting for a finished frame)
  //               (kill = false: wait for ongoing frame acquisition to stop)
  cvbres_t result = G2Freeze(cvbImage_.get(), true); 

  // Wait a short time to give the camera enough time so that we are able to access the camera 
  // without any restrictions (e.g. setting a GenICam feature which is only writable when the acquisition is stopped)
  this_thread::sleep(100);

  return result >= 0;
}

// ---------------------------------------------------------------------------
/// \brief Acquires an Image from this camera. 
///
/// \param [in] softwareTrigger If \b true a software trigger will be sent to 
///               the camera before acquiring the image. 
/// \throw runtime_error thrown when an error occurred while acquiring an image. 
// ---------------------------------------------------------------------------
void Cvb::Camera::acquireImage(cvbbool_t softwareTrigger)
{
  // send software trigger if requested
  if(softwareTrigger)
  {
    // Check again if the Software Trigger interface is supported
    // because it might be changed after changing settings in the camera.
    if(!CanSoftwareTrigger(cvbImage_.get()))
      throw CvbError("Software Trigger Interface not supported", CVC_ERROR(CVC_E_NOTSUPPORTED));
    
    STTrigger(cvbImage_.get(), 0);
  }

  // wait for next image to be acquired
  // (returns immediately if unprocessed image is in the ring buffer)
  cvbres_t result = G2Wait(cvbImage_.get());
  if(result < 0)
  {
    int errorCode = CVC_ERROR_FROM_HRES(result);

    if(errorCode == CVC_E_TIMEOUT)
      throw CvbError("Acquisition timeout (Is the device waiting for a trigger?)", result);
    else if (errorCode == CVC_E_GRABABORTED)
      throw CvbError("Acquisition error because grab was aborted", result);
    else
    {
      std::stringstream msg;
      msg << "Acquisition error (ErrorCode: " << errorCode << ")";
      throw CvbError(msg.str(), result);
    }
  }
}

// ---------------------------------------------------------------------------
/// \brief Returns the CVBImage Object 
///
/// \return The CVBImage object which is hold by this object.
// ---------------------------------------------------------------------------
Cvb::CvbImage Cvb::Camera::getCvbImage() const
{
  return cvbImage_;
}
