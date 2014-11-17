===========================================================================

  AVT Vimba for Linux 
  
  Latest Version: 1.3.0
  Release Date:    2014-August-19
===========================================================================

--------------------------------
Components and Version Reference  
--------------------------------

AVT Genicam Transport Layer modules
-----------------------------------
  GigE Transport Layer (AVTGigETL.cti)                  1.3.1*

APIs
----
  Vimba C API (libVimbaC.so)                            1.3.0*
  Vimba C++ API (libVimbaCPP.so)                        1.3.0*
  Image Transform Library (libAVTImageTransform.so)     1.2.0*

Tools
-----
  Vimba Viewer (VimbaViewer)                            1.1.3* (only x86 Linux)
  Vimba Class Generator (VimbaClassGenerator)           1.0.3* (only x86 Linux)

Third Party Libraries
----------
  TinyXML (not shipped with Vimba)                      2.6.2
  Qt                                                    4.8.4  (only x86 Linux)



-----------------------------
Tested Operating Systems
-----------------------------
AVT Vimba has been tested with the following 32 bit and 64 bit x86
operating systems:

   Ubuntu (Tested with version 12.04 LTS "Precise Pangolin")
   Debian (Tested with version 6 "Squeeze")
   Fedora (Tested with version 17 "Beefy Miracle")

   
AVT Vimba has been tested with the following 32-bit ARM
operating systems:

   Ubuntu hard-float (Tested with version 12.04 LTS "Precise Pangolin")
   Ubuntu soft-float (Tested with version 11.10 "Oneiric Ocelot")
   Angstrom hard-float (Tested with version 2012.12)
 
   If running soft-float applications on hard-float boards, it might become
   necessary to install additional runtime libraries for soft-float support.

AVT Vimba is most likely while not guaranteed to be compatible to follow up 
versions of the aforementioned environments.

Please note that 1394 support is not available for Linux.

Features
---------------------
Package for ARMv7 (new)
  - Support of Vimba C API
  - Support of Vimba C++ API
  - Support of GigE Transport Layer

Package for other Linux systems
  - Added a Vimba Tour document and a Vimba Quickstart Guide
  - Improved the other documents
  - Added examples for Vimba C and C++
  - Added an OpenMP version of the Vimba Image Transform Library

Vimba C
  - feature access for ancillary data
  - Made device discovery blocking
  - Added system feature GeVDiscoveryAllDuration for adjustable waiting time
  - Fixed issues with mixed feature names
  - Bug-fixes for improving stability

Vimba C++
  - feature access for ancillary data
  - Changes caused by bug fixes in Vimba C

Vimba Image Transform Library
  - Allowed more input for VmbSetImageInfoFromString
  - Corrected return codes
  - Removed transformations to Mono10/12/14 and big-endian data

GigE Transport Layer
  - Added a document for GigE camera features
  - Changed the supported GenTL version to 1.3 (e.g. new feature categories
    BufferHandlingMode and StreamInformation)
  - Separate features for heartbeat timeout and heartbeat interval
  - Adjustable device discovery waiting time

Vimba Viewer
  - Improved handling for GigE camera list changes
  - GUI usage improvements

Vimba Class Generator
  - Minor changes to appearance and documentation


------------
Known Issues
------------
- When experiencing trouble with image acquisition try to increase the priority
  of your application with "sudo -E nice -n -20 <command>".

GigE Transport Layer:
- A change of the available camera access modes cannot be reported for cameras
  in different subnets or with malconfigured IP addresses. These cameras can
  be accessed in configuration mode from different hosts simultaneously.

------------------------------
AVT Technical Software Support
------------------------------
You can reach the AVT Technical Software Support via the corresponding contact 
form for your region:

   Asia Pacific
   ------------
        http://www.alliedvisiontec.com/apac/support/contact-support.html 
   
   Europe, Middle East and Africa 
   ------------------------------
        http://www.alliedvisiontec.com/emea/support/contact-support.html
  
   Germany
   -------
        http://www.alliedvisiontec.com/de/support/support-kontaktieren.html

   The Americas
   ------------
        http://www.alliedvisiontec.com/us/support/contact-support.html

   China
   ------------
        http://www.alliedvisiontec.com/cn/support/contact-support.html
