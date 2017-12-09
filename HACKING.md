# Getting the code

This project uses git submodules.  You'll need to grab them with a command like:

```
$ git clone --recurse-submodules https://github.com/micolous/AndProx.git
```

Shallow clones won't work.  If you see missing compile dependencies from Gradle, you've probably done it wrong.

# Testing / Developing AndProx

AndProx can be imported into Android Studio using the Gradle files provided in this project.  Do not check in Android Studio project files into the source repository.

## With an emulator

> **Note:** There are some issues with current Proxmark3 firmware through an emulator, so this may not work.

The standard Android Emulator does **not** support USB pass-through.

You'll need to use another system emulator (eg: VirtualBox) and your own Android system images (eg: [Android-x86](http://www.android-x86.org/download)).  Android-x86 enables ADB over TCP debugging by default, so additional steps may be required if you use other images.

VirtualBox settings:

- Your user should be in `vboxusers`, otherwise USB will not work. You will need to log out and log in again for this to take effect.
- Create a new host-only adapter in VirtualBox preferences.

In the Virtual Machine:

- General/Basic: Use Linux 2.6 / 3.x / 4.x profile
- System/Motherboard: Base memory: 2048 MiB
- System/Motherboard: Boot device: Optical only
- System/Motherboard: Pointing Device: PS/2 Mouse
- Storage/IDE: Only `android-x86_64-6.0_r1.iso` should be inserted, enable "Live CD/DVD"
- Audio: Disable audio
- Network/Adapter 1: During setup, use Bridge or NAT. Once set up, use Host-only Adapter.
- USB: USB 1.1 controller should be enabled
- USB: Add device filter for vendor `9ac4` device `4b8f` (for current Proxmark3 firmware).
- USB: Add device filter for vendor `2d2d` device `504d` (for old Proxmark3 firmware).

Then when you start up the Android-x86 environment, enable debug features (Settings > About > click Build number 7 times).

Once you have the environment configured but *before* connecting with `adb`, snapshot the running system in VirtualBox so you can boot quickly.

Then in your host, connect to `adb` with `adb connect 192.168.56.101` (substituting with the actual IP address of the guest).

If prompted by Google Play Services to check for harmful / malicious software, and you do not have an active Internet connection in this VM (eg: using host-only adapter), press `Disagree`.  Otherwise the system may hang for a while attempting to connect to Google.

## With physical hardware

First you should test that your cables work by connecting a USB Mouse to your device.  It should light up and display a cursor on-screen when you move it.

> *If you have a device which uses **USB-C** (eg: Nexus 5X, 6P, Pixel C, Pixel Phone):*
>
> USB-C to Micro-B USB adapters do not work with Micro-B OTG cables. You need a USB-C to USB-A adapter.

Most Android devices only have one USB port, which means it's not possible to debug the application over USB and run the Proxmark at the same time.

However, you can enable TCP/IP debugging over WiFi, which will free up the USB port for the proxmark.  To use this:

1. Connect your device to your PC via USB.
2. Run `adb tcpip 5555` to switch your device to TCP/IP debugging mode
3. Disconnect the USB cable
4. Run `adb connect 192.0.2.2` (substituting with your phone's IPv4 address)

You can then switch back to usb debugging with `adb usb` or by restarting the device.

Or if your device is rooted, you can do this with:

```
su
setprop service.adb.tcp.port 5555
stop adbd
start adbd
```

Once TCP/IP debugging is enabled, you can use your Proxmark by plugging it into your Android device with a [USB-OTG cable](https://en.wikipedia.org/wiki/USB_On-The-Go) or USB-C to USB-A dongle.

# Code layout

* `app`: Contains the front-end Android application.  `au.id.micolous.andprox` namespace.
* `natives`: Contains wrappers onto the Proxmark3 client code.
* `third_party`: Contains third-party code which we link to.
  * `GraphView`: Charting and graphing library for Android.
  * `usb-serial-for-android`: Userspace Android library for interfacing with USB serial devices.
