// ---------------------------------------------------------------------------
/// \file Camera.hpp
/// \author S.Kinzler
///
/// \brief Declaration of the \c Camera class.
// ---------------------------------------------------------------------------

#pragma once

#include <string>
#include "CvbHandle.h"

namespace Cvb
{
  namespace this_thread
  {
    /// Platform agnostic sleep helper.
    void sleep(unsigned int mseconds);
  }

  /// \brief Represents a camera supporting image acquisition.
  ///
  /// It loads a vin driver and holds its image/driver instance as a CvbImage 
  /// object (smart pointer object).
  class Camera
  {
    CvbImage cvbImage_; ///< \internal The grabber image
  public:
    static const cvbbool_t SOFTWARE_TRIGGER;

    // Constructor 
    // -----------------------------------------------------------------------
    explicit Camera(const std::string &driver);

    // Public functions
    // -----------------------------------------------------------------------
    cvbbool_t startAcquisition();
    cvbbool_t stopAcquisition();
    void acquireImage(cvbbool_t softwareTrigger = false);
    CvbImage getCvbImage() const;

    cvbval_t getNumCameras() const;
    cvbval_t getPort() const;
    void switchCamPort(cvbval_t camPort);
  };
}
