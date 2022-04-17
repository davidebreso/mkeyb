## What is mKEYB

mKEYB is a minimum keyboard driver for xxDOS, requiring less than 1Kb of memory to support international keyboards, developed by Tom Ehlert at

[http://www.drivesnapshot.de/freedos/mkeyb.htm](http://www.drivesnapshot.de/freedos/mkeyb.htm)

The original version of mKEYB requires a 80286 or better machine. This repository hosts a modified version of mKEYB that can run on XT machines.

## How it works

mKEYB is so small because it relies on the BIOS to do most of the work.  It should work on any machine where the BIOS keyboard routines uses INT 15,4F to allow for keyboard translation, and implements the INT 16,5 service (Keyboard buffer write). All the required functionalities are usually present in AT, PS/2 and later class machines. This is not the case for XT machines, where different BIOSes implement different subsets of the above functionalities. 

From version 0.48 onwards, mKEYB tries to detect if the BIOS provides the required functionalities, and installs additional interrupt handlers in memory if they are not available.

## How to use it

`mkeyb /?` gives you a help screen, and `mkeyb /l` lists all available keyboard layouts. 

Try first to run it with the layout code and no other switches, e.g. `mkeyb it` for italian. If everything works, congratulations! mKEYB autodetected the functionalities provided by your BIOS and installed what is missing: you can enjoy your ~700 bytes driver. If not, see below for some hints.

### The driver loads but the keyboard remains with the default US layout.
Your BIOS do not use INT 15,4F to allow for layout translation. Try with the `/9` switch: `mkeyb it /9`.

This switch installs a new handler for INT9 (keyboard interrupt) that calls INT 15,4F to translate the layout. The handler should work on any machine
with a keyboard controller that is compatible with the 8255 PPI of the original IBM PC and XT: data buffer at port 60h and status register at port 61h. 
This includes also machines with AT keyboard controllers, that are backward compatible with the 8255 PPI. If your machine uses a keyboard controller that answers on different ports, the handler will most likely hang your keyboard.

`/9-` disables installation of the INT9 handler even if autodetection decided that it is needed.

### The driver loads, some keys works but others do not (nothing happens when I press them).
Your BIOS do not implement the INT 16,5 service to insert a new keystroke in the keyboard buffer. Try with the `/G` switch: `mkeyb it /G`.
This switch installs a new handler for INT 16 (keyboard services) with the required functionality. 

You can combine /G with /9: `mkeyb it /9 /G`. 

`/G-` disables installation of the INT16 handler even if autodetection decided that it is needed.

## Standard and Enhanced keyboards

PC keyboards came in two flavours: "standard" keyboards with 83 or 84 keys, common on XT class machines, and "enhanced" keyboards with 101 or 102 keys, common on AT, PS2 and later machines.

mKEYB supports both keyboard types. An enhanced keyboard layout is available for all languages. For some languages also a custom layout for standard keyboards is present. mKEYB can autodetect the keyboard type and selects the appropriate keyboard layout, if available for the language. If the standard keyboard layout is not available for the selected language, mKEYB patches the enhanced keyboard layout to use Ctrl+Alt instead of AltGr (not available on standard keyboards). This pached layout may not be completely accurate.

The `/E` switch forces an enhanced keyboard layout, while `/S` forces a standard keyboard layout.

## How to uninstall it

To uninstall the driver type `mkeyb /u` or `mkeyb us` (US keyboards do not need a driver).

## Known limitations

* mKEYB is known to work on my machine, an Amstrad PC5086 with and enhanced 101 keys keyboard. Consider it untested on anything else.
* Most of the layouts are for 101/102 keys enhanced keyboards only. They are not accurate for 83 keys keyboard.
* Autodetect of BIOS features and keyboard type may not work.
* The INT 9 handler is written for controllers compatible with the 8255 PPI, and may have unpredictable results with non-standard keyboard controllers

## License 

This program and its source code is distributed under the terms of the GNU GPL with one major exception:

you may use any exepacker you want to process the resulting executable.

