===========================================================================

  Pylon software suit for Linux from Basler 
  
===========================================================================

----------
Components
----------
doc/*                            # HTML documentation
Samples/*                        # sample files
pylonSDK-4.0.x-<ARCH>.tar.gz     # pylon SDK and runtime files
69-basler-cameras.rules          # udev rules file
README
INSTALL
setup-usb.sh                     # installer for usb support


------------
Installation
------------

After Downloading the package from the company website [Link] (http://www.baslerweb.com/Support_SW_Downloads-18498.html), the installation of pylon for Linux is described in the INSTALL text document.

-------------
Documentation
-------------

The installation archive includes a "doc" sub-folder containing the 
pylon Programmer's Guide and API reference documentation. Open the 
index.html file with an internet browser.

---------------
Sample Programs
---------------

The installation archive includes a set of sample programs. These sample 
programs are simple command line programs showing the basic pylon use 
cases. They are located in the "Samples" folder. The folder contains a 
top-level Makefile that can be used to build the different sample programs.

Before calling "make" you must setup your environment for pylon to find the 
necessary dependencies:
  cd Samples
  source <path to pylon>/bin/pylon-setup-env.sh <path to pylon>
  make

---------------
Camera Emulator
---------------

In addition to the GigE Vision transport layer, this release contains a transport layer able to create simple camera emulator devices that allow you to develop applications without having a physical camera device attached. 
The emulator has very limited functionality, but is able to create test images for different bit depths.

The number of available emulator devices can be controlled by exporting the PYLON_CAMEMU environment variable. For example,

   export PYLON_CAMEMU=2

will provide two emulator devices. These devices are accessible both by using the pylon API and the pylon Viewer program.

When PYLON_CAMEMU is not set, no emulator devices are provided.


-----------
Readme file
-----------
It contains general describtion about the package components in addition it also contains some problems and solutions.


