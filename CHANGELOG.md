# FETK Changelog

## 1.9.1

Jan 21, 2022

* Fixed missing headers from punc

## 1.9.0

Jan 21, 2022

* Added capability for a fully static build
* Apple BLAS for Macs
* Win dependencies v0.4.0
* Install and package CMake module files
* SuperLU built from the SuperLU repo

## 1.8.1

Oct 12, 2021

* Fixed Windows system type
* Added version badge instead of hardcoded version in README.md

## 1.8.0

Sep 27, 2021

* Added missing file `mc.h` to `mc/base`
* Windows dependencies now extracted from Electrostatics/cache repo
* Add -fPIC compile flag
* Switch Windows build to 32-bit (x86)
* Enable PUNC, GAMER, and MC in the Windows build
* Fix Windows compatibility issues in PUNC
    * `access()` from `unistd.h` replaced by `_access()` from `io.h` in Windows
    * Added check for `_WIN32` in some preprocessor logic
    * Fixed redefinition of `isatty()`
    * Deconflict use of `complex` in `f2c` by replacing `complex` typedef with `realcomplex`

## 1.7.0

Sep 3, 2021

* Fixed install directories for include files

## 1.6.0

Aug 4, 2021

* Separated Release and Build workflows, and automated tag creation
* Automated build and release on GitHub Actions
* Platforms supported: Ubuntu, MacOS, Windows

## 1.5
 (12/07/2010): 

Added preliminary python wrapping via swig and autoconf.

## 1.4 (08/11/2010): 

Applied more SMOL patches (more data passed to PDE obj).

## 1.3
 (08/02/2010): 

Applied some SMOL patches (two more fields in TT struct).

## 1.2
 (07/20/2010): 

Applied some build patches contributed by downloaders.

## 1.1 
(07/13/2010): 

Minor fixes, mostly to address Doxygen warning messages.

## 1.0 
(06/28/2010): 

Initial public release.

