# AndProx changelog

## v2.0.5, not released yet

- Proxmark version: [3.1.0](https://github.com/Proxmark/proxmark3/tree/v3.1.0) (clean)
- Source code: (not yet)
- APK: (not yet)
- Firmware: (same as 2.0.4) https://github.com/AndProx/AndProx/releases/download/v2.0.4/fullimage.elf.zip

Changes:

- New: Prevents sleep (turning off the screen) by default. Can be disabled in settings.
- Fixed: Bootloader version is now ignored for all version checks. This impacts devices that have
  incorrectly built bootloaders; but this doesn't actually impact compatibility.
- Fixed: Removes background "ping" which broke `snoop` operations.
- Cleanup: Moved license notices into files.

## v2.0.4, released 2018-12-01

- Proxmark version: [3.1.0](https://github.com/Proxmark/proxmark3/tree/v3.1.0) (clean)
- Source code: https://github.com/AndProx/AndProx/tree/v2.0.4
- APK: https://github.com/AndProx/AndProx/releases/download/v2.0.4/andprox-2.0.4.apk
- Firmware: https://github.com/AndProx/AndProx/releases/download/v2.0.4/fullimage.elf.zip

Changes:

- New: PM3 v3.1.0! [See upstream change log](https://github.com/Proxmark/proxmark3/blob/master/CHANGELOG.md#v3102018-10-10).
- New: Select/copy text from the output buffer.
- New: Button which scrolls to the bottom of the output buffer.
- New: Support for connecting to a PM3 over TCP (useful for debugging and ChromeOS devices).
- Fixed: PM3 devices with Iceman's bootloader are no longer blocked (mainly impacts RDV4.0).
- Fixed: Commands that use `printf` should now come through correctly.
- Cleanup: Documentation cleanups / improvements.

Release notes:

- Mainline firmware 3.1.0 or later is required to use this build.

- `INTERNET` permission was added to support connecting to PM3 over TCP.

- While TCP support is now available, the manifest blocks installation on devices without support
  for USB Host. This is to avoid confusion on devices _without_ USB Host that have no easy way to
  set up a serial-over-TCP proxy (ie: everything that _isn't_ ChromeOS or the Android Emulator).

  ChromeOS support is still untested, and until I have a good way to allow use on ChromeOS but _not_
  every other Android device, this will continue to be blocked.

  With a little `socat` command, this allows you to [easily debug on the Android
  Emulator](./docs/debugging/android-emulator.md).

## v2.0.3, released 2018-09-09

- Proxmark version: 3.0.1 [(+400 bed3db8f)](https://github.com/proxmark/proxmark3/tree/bed3db8f1dea15b9e998c3c4c432c58c5eb565eb)
- Source code: https://github.com/AndProx/AndProx/tree/v2.0.3
- APK: https://github.com/AndProx/AndProx/releases/download/v2.0.3/andprox-2.0.3.apk
- Firmware: https://github.com/AndProx/AndProx/releases/download/v2.0.3/fullimage.elf.zip

Changes:

- New: Antenna tuning GUI, with graphs!
- New: HID IClass support, and everything else new from PM3 since last version.
- New: AndProx now reports when it is waiting for PM3.
- New: Automated unit tests.
- New: AndProx will now refuse to work with devices with incorrect firmware.
- Fixed: Several resource leaks.
- Fixed: Pressing `ENTER` with a hardware keyboard on some devices would crash AndProx.
- Fixed: Firmware issue with PM3 not enumerating on some devices. Requires firmware update.
- Fixed: All the patches for AndProx are now in Proxmark3!
- Cleanup: PM3 now uses Android's zlib.
- Cleanup: Removed some unused USB serial drivers.

## v2.0.2, released 2017-12-26

- Proxmark version: 3.0.1 (+137 9d8b41bd)
- Source code: https://github.com/AndProx/AndProx/tree/v2.0.2
- APK: https://github.com/AndProx/AndProx/releases/download/v2.0.2/andprox-2.0.2.apk
- Firmware: https://github.com/AndProx/AndProx/releases/download/v2.0.2/fullimage.elf.zip

Changes:

- Fixes version number displayed for Proxmark3 -- this includes v3.0.1.

- Works around [Proxmark issue 527](https://github.com/Proxmark/proxmark3/issues/527), so some functionality is no longer available (HID IClass).

## v2.0.1, released 2017-12-10

- Proxmark version: 3.0.1 (mislabelled in-app)
- Source code: https://github.com/AndProx/AndProx/tree/v2.0.1

This is the initial version of AndProx.

- Many LF commands appear to work.

- LF graphs are not available yet.

- Scripting doesn't work properly, but most of the ground work is there.

- Most HF card functions don't work properly yet (likely to be a firmware issue).

- `hf mf hardnested` commands use a lot of memory. In the event of running out of memory, it will
  close the application without warning.

- Anything output from `printf` won't be displayed.  `PrintAndLog` will be displayed, but will not
  be written to disk.

- Probably doesn't exit or sleep cleanly, causing high battery use. Swipe the app away from the App
  Switcher when done, and unplug the PM3.

## v1.x

These were earlier porting attempts, that were not released publicly.

It reimplemented the Proxmark3 communications protocol in Java, and then called out to Proxmark3
functions for computationally difficult functionality.
