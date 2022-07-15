# xBaK

## Introduction

xBaK is a fan-made remake of the classic Sierra computer RPG "Betrayal at Krondor" running on linux. xBaK is licensed under the GPL version 3. See LICENSE for more information.

## Requirements

Required tools and software (minimum version is listed):
* SDL-1.2.13
* SDL_mixer-1.2.11
* SDL_sound-1.0.3

xBaK uses SDL_sound to convert the MIDI sound to WAV format. Therefore
SDL_sound must be built with Timidity++ support. SDL_sound also requires a GUS
compatible set of sound patches. These should probably come with your linux
distribution.

Note that SDL_mixer must be built _without_ Timidity++ support! Building both
SDL_Sound and SDL_mixer with Timidity++ support will result in both libraries
providing the same functions originally from Timidity++. This will inevitably
lead to either build time or run time problems.

xBaK should build and run without SDL_mixer and SDL_sound, but there will be no
sound.

## Building

Required tools and software for building xBaK:
* CMake
* C++ compiler tool chain
* development versions of the required SDL libraries

To build on linux change to the directory where the xBaK sources are extracted.
Next run "cmake ." and, if no errors are reported, continu to run "make".
There is no need to run "make install" yet. The resulting executables can be
found in the "./src" subdirectory.

Building xBaK on other platforms may be possible but not actively supported.

## Running

To play the game simply start the xbak executable. Please keep in mind that
this is still a work in progress. Many features are either buggy or not
implemented at all.

Notes for running the xBaK game:
* Original data files
  xBaK requires the following files, containing resource data:
  - krondor.cfg
  - krondor.rmf
  - krondor.001
  - frp.sx
  - startup.gam
  Note that the filenames are in lower case. You might need to rename them.
  These original data files must be stored in one of the following
  directories:
   - ./
   - /krondor/
   - ./krondor/
   - ../krondor/
   - /opt/krondor/
   - /bakcd/
   - ./bakcd/
   - ../bakcd/
   - /opt/bakcd/
* Other files
  On Linux/BSD/Unix platforms xbak will create its own directory structure
  for user specific data on startup. The directory structure is as follows:
    ~/.xbak           # for user data
    ~/.xbak/capture   # for screenshots
    ~/.xbak/games     # for saved games
  On other platforms the current directory is used for everything, except
  the original Betrayal at Krondor data files mentioned above.
* Grabbing keyboard and mouse
  Initially the keyboard and mouse are not grabbed. Grabbing the input
  can be toggled by pressing the F12 key. Or, if the input is not grabbed,
  move the mouse inside the xbak application window and press the left
  or right mouse button to grab the input. When the input is grabbed,
  pressing the middle mouse button will release the grab on input.
  Note: the mouse is not grabbed if debugging support is enabled.
* Screenshots
  Screenshots can be made using the F11 key. The screenshots will be saved
  in the dedicated screenshot directory mentioned earlier. The images are
  stored in BMP format. The filenames have the following form:
  xbak_<nnn>.bmp, with <nnn> ranging from 001 to 999. Pre-existing screenshot
  files will be overwritten.

Besides the xBaK game engine several other executables are available. Most of
those are just utilities that are only helpful for developing xBaK. The only
other application that can be useful for end users is convertresource. With
convertresource one can extract the data files from, and recombine into the
resource archive. It is also possible to extract the individual bitmap images
from the .BMX data files.
