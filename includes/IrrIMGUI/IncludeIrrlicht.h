/**
 * @file   IncludeIrrlicht.h
 * @author Andre Netzeband
 * @brief  Helper file for including irrlicht from the correct location.
 * @addtogroup IrrIMGUI
 */

#ifndef IRRIMGUI_SOURCE_INCLUDEIRRLICHT_H_
#define IRRIMGUI_SOURCE_INCLUDEIRRLICHT_H_

// disable CPPUTEST new macro for Irrlicht library
#if CPPUTEST_USE_NEW_MACROS
   #undef new
#endif

#ifndef _IRRIMGUI_SUBDIR_IRRLICHT_INCLUDE_
#include <irrlicht.h>
#else  // _IRRIMGUI_SUBDIR_IRRLICHT_INCLUDE_
#include <Irrlicht/irrlicht.h>
#endif // _IRRIMGUI_SUBDIR_IRRLICHT_INCLUDE_

// enable CPPUTEST new macro for further headers
#if CPPUTEST_USE_NEW_MACROS
   #include <CppUTest/MemoryLeakDetectorNewMacros.h>
#endif

#endif // _IRRIMGUI_SUBDIR_IRRLICHT_INCLUDE_
