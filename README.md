# WinOver
WinOver is a small utility library that provides a less intrusive alternative to DirectX hooking for developers looking to create overlays for apps or games. 
Check out the Example folder for a simple transparent text overlay example.

## Features
- Lightweight. The entire DLL is under 1MB.
- Free and open source using the MIT license.
- Zero dependencies.
- Extensible. Window subclassing enables full customization of the overlay—you can even override default behaviors.
- High compatibility. The code can be used with any graphics backend.
- Unintrusive. The overlay does not interact directly with the target program, guaranteeing that it won't be detected by anticheat.

## Limitations
- Requires C++.
- No MFC support (yet).
- Windows only.
- Poor support for classic fullscreen apps (see below).

## Why doesn't it work for some fullscreen games?
Games using DirectX 11 or lower that run in exclusive fullscreen mode have exclusive privileges to draw over the entire screen, as the name suggests. 
Because of this, no other apps can draw to the screen while these programs have focus, and thus the overlay doesn't appear. 
However, Windows is slowly phasing out this kind of application, and it seems that DirectX 12 apps are not truly fullscreen, meaning other windows *can* actually draw on top of them. 
Additionally, Windows 10 has a new feature called "fullscreen optimization" that makes fullscreen apps work with overlays at the cost of some performance. 
This feature should in theory eliminate the need to use borderless windowed mode.
You can turn it on or off in the compatibility tab of the properties window for any application.

## How to use WinOver in your app
WinOver is distributed as a dynamic link library, though you could probably just as easily compile it as a shared or static library with a few tweaks if you wanted to. 
The first step is to clone the repository. Then, in your visual studio project, add a reference to the WinOver project. 
All the functions you need to create and use overlays can be found in the public header file, winover.h, located in the Inc folder. 
Intellisense should be able to find them automatically.
If you want to use runtime linking instead, just make sure that you don't unload WinOver.dll while any overlay windows are still open. 
This will cause the program to crash with an access violation. 
Every API function is fully documented so check out the header file and look at the example app to learn more. 
