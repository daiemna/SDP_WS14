// ---------------------------------------------------------------------------
/// \file CvbHandle.cpp
/// \author S.Kinzler
///
/// \brief Declaration and implementation of the \c CvbHandle class.
///        This class represents reference counted CVB objects as
///        a safe RAII wrapper (Resource Acquisition Is Initialization).
///        This results in safer, more readable and more compact code. 
///        And the best of it all: you don't need to keep the reference count 
///        in mind. Just work with copyable and assignable objects and 
///        use the CVB object as your "smart pointer". 
// ---------------------------------------------------------------------------
#pragma once

#include <iCVCImg.h>
#include <iCVGenApi.h>

namespace Cvb
{
  template <typename HandleType>
  class CvbHandle
  {
    // Safe bool idiom (protects against some unexpected C++ parses)
    typedef void (CvbHandle::*bool_type)() const;
    void SafeBool() const {};
    HandleType handle_;

  public:
    // Defines whether or not the image is shared when constructing this object.
    enum ShareMode
    {
      share,    // Use this when getting the image from an ActiveX control
      dontShare // Use this when getting a new image from a library function
    };

    // Creates an empty CvbHandle
    CvbHandle() : handle_(NULL) {}

    // Creates a CvbHandle object from the given image handle and uses the given 
    // share mode (library version)
    CvbHandle(IMG image, ShareMode mode)
      : handle_(image)
    {
      if(mode == share)
      {
        ShareObject(handle_);
      }
    }

    // Creates a CvbHandle object from the given image handle and uses the given 
    // share mode (ActiveX version)
    CvbHandle(intptr_t image, ShareMode mode)
      : handle_(reinterpret_cast<IMG>(image))
    {
      if(mode == share)
      {
        ShareObject(handle_);
      }
    }

    // Destructor (not intended for deriving from)
    ~CvbHandle()
    {
      ReleaseObject(handle_);
    }

    // Copy
    CvbHandle(const CvbHandle &image)
      : handle_(image.handle_)
    {
      ShareObject(handle_);
    }

    // Copy
    CvbHandle & operator =(const CvbHandle &image)
    {
      if(this != &image)
      {
        CvbHandle(image).swap(*this);
      }
      return *this;
    }

    // Validity check (handle non-null).
    operator bool_type() const { return handle_ != NULL ? &CvbHandle::SafeBool : 0; }

    // Inequality check
    bool operator !=(const CvbHandle &other) { return handle_ != other.handle_; }

    // Equality check
    bool operator ==(const CvbHandle &other) { return handle_ == other.handle_; }

    // Swaps this object with the other
    void swap(CvbHandle &other)
    {
      IMG tmp = handle_;
      handle_ = other.handle_;
      other.handle_ = tmp;
    }

    // Gets the managed image
    HandleType get() const { return handle_; }

    // Get for ActiveX controls
    intptr_t getForOCX() const { return reinterpret_cast<intptr_t>(handle_); }

    // Resets the image handle for this object and releases the image.
    void reset()
    {
      CvbHandle().swap(*this);
    }
  };

  typedef CvbHandle<IMG> CvbImage;
  typedef CvbHandle<NODE> Node;
  typedef CvbHandle<NODEMAP> NodeMap;
}
