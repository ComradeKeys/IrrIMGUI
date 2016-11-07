/**
 * @file   IMGUIHelper.h
 * @author Andre Netzeband
 * @brief  Contains helper functions for the IMGUI handling.
 * @addtogroup IrrIMGUI
 */

#ifndef LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_IMGUIHELPER_H_
#define LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_IMGUIHELPER_H_

// module includes
#include <IrrIMGUI/IrrIMGUIConfig.h>

/**
 * @addtogroup IrrIMGUI
 * @{
 */

namespace IrrIMGUI
{
  /// @brief Updates the values for an IMGUI Frame, like delta time, input events and screen size.
  /// @param pDevice       Is a pointer to an Irrlicht device.
  /// @param pEventStorage Is a pointer to the event storage. If this pointer is NULL, no input event update is performed.
  /// @param pLastTime     Is a pointer to a variable where the time from the last update is stored (in seconds).
  IRRIMGUI_DLL_API void updateIMGUIFrameValues(irr::IrrlichtDevice * const pDevice,  CIMGUIEventStorage * const pEventStorage, irr::f32 * const pLastTime);
}

/**
 * @}
 */

#endif /* LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_IMGUIHELPER_H_ */
