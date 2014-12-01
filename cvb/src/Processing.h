// ---------------------------------------------------------------------------
/// \file Processing.h
/// \author S.Kinzler
///
/// \brief Declaration of the processing functions.
// ---------------------------------------------------------------------------
// 
#pragma once

#include "CvbHandle.h"

namespace Cvb
{
  cvbbool_t LinearImageAccess(const CvbImage &image);
  cvbbool_t ShowHistogram(const CvbImage &image);
}
