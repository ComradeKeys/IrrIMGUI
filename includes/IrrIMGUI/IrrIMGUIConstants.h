/**
 * @file   IrrIMGUIConstants.h
 * @author Andre Netzeband
 * @brief  Contains constants values for IrrIMGUI.
 * @addtogroup IrrIMGUI
 */

#ifndef LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_IRRIMGUICONSTANTS_H_
#define LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_IRRIMGUICONSTANTS_H_

// library includes
#include "IncludeIMGUI.h"

/**
 * @addtogroup IrrIMGUI
 * @{
 */
namespace IrrIMGUI
{

/// @brief Contains constant values for IrrIMGUI:
namespace Const
{
  enum EConstants {
    /// @brief The number of mouse buttons supported by IMGUI.
    NumberOfMouseButtons = 5,
  };

#ifdef IRRIMGUI_CONFIG_SIZEOF_FROM_CLASSMEMBER
  static_assert(NumberOfMouseButtons == sizeof(ImGuiIO::MouseDown)/sizeof(bool), "The number of mouse buttons are different in IMGUI and IrrIMGUI!");
#endif // IRRIMGUI_CONFIG_SIZEOF_FROM_CLASSMEMBER

}
}

/**
 * @}
 */

#endif /* LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_IRRIMGUICONSTANTS_H_ */
