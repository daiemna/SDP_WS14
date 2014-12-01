// ---------------------------------------------------------------------------
/// \file GenICam.h 
/// \author S.Kinzler
///
/// \brief Declaration of the \c GenICam class.
// ---------------------------------------------------------------------------

#pragma once

#include "Camera.h"

namespace Cvb
{
  /// \brief Uses CVB GenApi functions to access  GenICam features of ac 
  ///        camera object.
  ///        
  /// It shows the access of some basic camera features and provides generic
  /// functions to read features. 
  class GenICam
  {
    NodeMap nodeMap_;
    Node getNode(const std::string &name) const;
  public:
    // Constructor 
    // -----------------------------------------------------------------------
    explicit GenICam(const Camera &camera);

    // Public functions
    // -----------------------------------------------------------------------
    cvbbool_t setTriggerMode(cvbbool_t activateTrigger);
    cvbbool_t setTriggerSource(const std::string &triggerSource);
    cvbbool_t setExposureTime(cvbval_t exposureTime);
    std::string getStringFeature(const std::string &featureName) const;
  };
}
