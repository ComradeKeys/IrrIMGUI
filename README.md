# ImGui bindings for Irrlicht2

About
=====
Originally forked from IrrIMGUI by ZhalGraf, his original wrapper is very helpful to those who are stuck on the old Irrlicht and need a usable GUI. This wrapper works with Irrlicht2 (also known as IrrlichtBAW) this wrapper is the successor to the original IrrIMGUI.
IrrlichtBAW does not have any GUI system built in, so IrrIMGUI allows you to easily create a GUI for your game using IMGUI. IMGUI is also very performant and has a very minimal performance hit. It is very useful for implementing everything from in game menu's and HUD's. If your project uses IrrIMGUI and you would not mind sending some screenshots; I would be very happy to include them in this README.

Usage
=====
The code in the examples/ folder is full of ways to use IrrIMGUI in your project and showing the multiple use cases for the IrrIMGUI. IrrlichtBAW has no built in GUI so at the time of this writing IrrIMGUI is the only GUI wrapper in existance for IrrlichtBAW.
IrrIMGUI uses CMake, so compiling and using IrrIMGUI is about the same as any other library that uses CMake. You can compile the library statically or dynamically and it needs to link to IrrlichtBAW and have IMGUI found as well. IMGUI is not included because if IMGUI were bundled you might not be getting the newest IMGUI. If you would like to add any additional examples to IrrIMGUI feel free to make a pull request.

Licensing
=========
This software is under the Standard Library Function License which prohibits inclusion in proprietary software, however software under other free software licenses are available. Examples of compatible software licenses would be
- GNU GPL (any variant)
- BSD (any variant)
- zlib
- MIT

If you would like a full zlib exception to the license please contact Brigham Keys at bkeys@bkeys.org

Known Issues
============
- Picture example does not work properly, font texture is loaded instead of image
- The widgets are not being clipped from the bottom of the window
- Double rendering example does not work, we have to figure out how IrrlichtBAW does this
- Thread safe compiling does not work; you have to run make twice to get the examples built
All future issues are going to be documented in GitHubs issue tracker

Thank you
=========
- Brigham Keys for porting IrrIMGUI to Irrlicht2
- ZhalGraf for writing the original IrrIMGUI
- The author of the SDL2 example for imgui
- BAW for making Irrlicht2