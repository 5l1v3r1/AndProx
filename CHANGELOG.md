# AndProx changelog

## v2.0.3, not released yet

- Proxmark version: 3.0.1 (+345 8cd64fc3)
- Source code: (git master)
- APK: (none yet)
- Firmware: (none yet)

Changes:

- Added: Antenna tuning GUI, with graphs!
- Added: HID IClass support, EMV support.
- Fixed a number of resource leaks.
- Fix an issue where AndProx would crash on some devices when pressing `ENTER` with a hardware keyboard.
- Make it obvious when AndProx is waiting for PM3.

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
