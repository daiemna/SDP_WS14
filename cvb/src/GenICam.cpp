// ---------------------------------------------------------------------------
/// \file Camera.cpp
/// \author S.Kinzler
///
/// \brief Implementation of the \c GenICam class.
///        This object uses CV GenApi functions to access
///        GenICam features of a given Camera object
///        It shows the access of some basic camera features
///        and provides functions to access features over generic functions
///        where you need to know the feature name of the GenICam feature. 
// ---------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <vector>
#include <iCVGenApi.h>
#include <iCVCDriver.h>
#include "GenICam.h"
#include "CvbError.h"

// ---------------------------------------------------------------------------
/// \brief Constructor for the GenICam object
///
/// \param [in]   pCamera   smart pointer to camera object which is used with this 
///                         GenICam Object
// ---------------------------------------------------------------------------
Cvb::GenICam::GenICam(const Camera &camera)
{
  // Check if given Camera supports the NodeMapHandle interface
  // and get the NodeMap 
  if(CvbImage image = camera.getCvbImage())
  {
    if(!CanNodeMapHandle(image.get()))
      throw CvbError("GenICam access not possible: NodeMapHandle interface not supported");

    NODEMAP hNodeMap = NULL;
    cvbres_t result = NMHGetNodeMap(image.get(), hNodeMap);

    if(result < 0)
      throw CvbError("GenICam access not possible: Could not get NodeMap from Camera", result);

    // adopt life-time 
    // (load creates NodeMap object and we don't need the handle here anymore)
    nodeMap_ = NodeMap(hNodeMap, NodeMap::dontShare);
  }
  else
  {
    throw std::logic_error("No CvbImage present in camera");
  }
}


// ---------------------------------------------------------------------------
/// \brief Helper to get a node smart pointer.
/// 
/// \param [in] name Node name
/// \return \b Node object or invalid if \a name not found.
// ---------------------------------------------------------------------------
Cvb::Node Cvb::GenICam::getNode(const std::string &name) const
{
  NODE hNode = NULL;
  cvbres_t result = NMGetNode(nodeMap_.get(), name.c_str(), hNode);
  if(result < 0)
    return Node();
  else
    return Node(hNode, Node::dontShare); // adopt life-time
}

// ---------------------------------------------------------------------------
/// \brief Sets the TriggerMode feature to the given value.
///
/// \param [in] activateTrigger \b true to enable the trigger; \b false for off.
// ---------------------------------------------------------------------------
cvbbool_t Cvb::GenICam::setTriggerMode(cvbbool_t activateTrigger) 
{
  cvbres_t result = CVC_ERROR(CVC_E_ERROR);
  if(Node triggerModeNode = getNode("TriggerMode"))
  {
    if(activateTrigger)
      result = NSetAsString(triggerModeNode.get(), "On");
    else
      result = NSetAsString(triggerModeNode.get(), "Off");
  }

  return result >= 0;
}


// ---------------------------------------------------------------------------
/// \brief Sets the TriggerSource feature to the given \a triggerSource
///        value.
///
/// \param [in] triggerSource  The string to be set as TriggerSource 
///                               (e.g. "Software" for software trigger)
// ---------------------------------------------------------------------------
cvbbool_t Cvb::GenICam::setTriggerSource(const std::string &triggerSource)
{
  cvbres_t result = CVC_ERROR(CVC_E_ERROR);
  if(Node triggerSourceNode = getNode("TriggerSource"))
  {
    result = NSetAsString(triggerSourceNode.get(), triggerSource.c_str());
    if(result < 0)
      std::cerr << "[ERROR] Error setting TriggerSource (" << triggerSource << "): " << CVC_ERROR_FROM_HRES(result) << std::endl;
  }
  else
  {
    std::cerr << "[ERROR] Error getting TriggerSource node" << std::endl;
  }
  return result >= 0;
}

// ---------------------------------------------------------------------------
/// \brief Sets the ExposureTime feature to the given value
///        If "ExposureTime" is not available it is tried to set "ExposureTimeAbs"
///        which is used by some cameras. 
///
/// \param [in] exposureTime Exposure time value in microseconds
// ---------------------------------------------------------------------------
cvbbool_t Cvb::GenICam::setExposureTime(cvbval_t exposureTime)
{
  Node exposureTimeNode = getNode("ExposureTime");
  // check for fall-back name
  if(!exposureTimeNode)
    exposureTimeNode = getNode("ExposureTimeAbs");
  
  cvbres_t result = CVC_ERROR(CVC_E_ERROR);
  if(exposureTimeNode)
    result = NSetAsInteger(exposureTimeNode.get(), exposureTime);

  return result >= 0;
}

// ---------------------------------------------------------------------------
/// \brief Get a string from a given featureName
///
/// \param [in] featureName  The feature name of the feature which need to be used
/// \return                  string of the given feature
///           
// ---------------------------------------------------------------------------
std::string Cvb::GenICam::getStringFeature(const std::string &featureName) const
{
  if(Node node = getNode(featureName))
  {
    size_t size = 0;
    cvbres_t result = NGetAsString(node.get(), NULL, size);
    if(result < 0)
      std::cerr << "[ERROR] Error reading string from " << featureName << " feature: " << CVC_ERROR_FROM_HRES(result) << std::endl;
    if(size <= 1)
      return std::string();
    std::vector<char> buffer(size);
    NGetAsString(node.get(), &buffer[0], size);
    return std::string(&buffer[0]);
  }
  else
  {
    std::cerr << "[ERROR] " << featureName << " not available" << std::endl;
    return std::string();
  }
}

