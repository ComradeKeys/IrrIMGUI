# ImGui bindings for Irrlicht2

Originally forked from IrrIMGUI by ZhalGraf, his original wrapper is very helpful to those who are stuck on the old Irrlicht and need a usable GUI. This wrapper works with Irrlicht2 (also known as IrrlichtBAW) 

Known Issues
============
- Picture example does not work properly, font texture is loaded instead of image
- The widgets are not being clipped from the bottom of the window
- Thread safe compiling does not work; you have to run make twice to get the examples built

Thank you
=========
- Brigham Keys for porting IrrIMGUI to Irrlicht2
- ZhalGraf for writing the original IrrIMGUI
- The author of the SDL2 example for imgui
- BAW for making Irrlicht2