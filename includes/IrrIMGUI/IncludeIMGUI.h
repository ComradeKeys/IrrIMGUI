/**
 * @file   IncludeIMGUI.h
 * @author Andre Netzeband
 * @brief  Helper file for including IMGUI and applying the correct settings.
 * @addtogroup IrrIMGUI
 */

#ifndef IRRIMGUI_SOURCE_INCLUDEIMGUI_H_
#define IRRIMGUI_SOURCE_INCLUDEIMGUI_H_

// disable CPPUTEST new macro for IMGUI library
#if CPPUTEST_USE_NEW_MACROS
   #undef new
#endif

// first include the config file to setup IMGUI correctly
#include "IrrIMGUIConfig.h"
#include <IMGUI/imgui.h>

// enable CPPUTEST new macro for further headers
#if CPPUTEST_USE_NEW_MACROS
   #include <CppUTest/MemoryLeakDetectorNewMacros.h>
#endif

#endif // IRRIMGUI_SOURCE_INCLUDEIMGUI_H_
