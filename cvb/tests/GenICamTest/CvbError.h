#pragma once

#include <stdexcept>
#include <CVCError.h>

namespace Cvb
{
  // -------------------------------------------------------------------------
  /// \brief Contains the error reason as a string and the CVB error code. 
  // -------------------------------------------------------------------------
  class CvbError
    : public std::runtime_error
  {
    CVC_ERROR_CODES code_; ///< \internal Error code.
  public:
    /// Creates the error with the given \a message and \a hres.
    CvbError(const std::string &message, cvbres_t hres)
      : std::runtime_error(message)
      , code_(static_cast<CVC_ERROR_CODES>(CVC_ERROR_FROM_HRES(hres)))
    {
    }
    /// Creates the error with the given \a message and default error code.
    CvbError(const std::string &message)
      : std::runtime_error(message)
      , code_(CVC_E_ERROR)
    {
    }
    /// Gets the error CVB code.
    CVC_ERROR_CODES code() const { return code_; };
  };
}