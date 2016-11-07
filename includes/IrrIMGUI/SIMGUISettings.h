/**
 * @file       SIMGUISettings.h
 * @author     Andre Netzeband
 * @brief      A storage the settings of the IMGUI.
 * @addtogroup IrrIMGUI
 */

#ifndef IRRIMGUI_INCLUDE_IRRIMGUI_SIMGUISETTINGS_H_
#define IRRIMGUI_INCLUDE_IRRIMGUI_SIMGUISETTINGS_H_

// module includes
#include "IrrIMGUIConfig.h"

/**
 * @addtogroup IrrIMGUI
 * @{
 */

namespace IrrIMGUI
{

  /// @brief Stores the settings of the IMGUI.
  struct IRRIMGUI_DLL_API SIMGUISettings
  {
    public:

      /// @brief Constructor to set the standard settings.
      SIMGUISettings(void):
        mIsGUIMouseCursorEnabled(true),
        mIsIMGUIMemoryAllocationTrackingEnabled(true)
      {}

      /// @{
      /// @name Settings

      /// @brief When this is true, the IMGUI draws it's own mouse courser and the system mouse cursor will turned off automatically (default: true).
      bool mIsGUIMouseCursorEnabled;

      /// @brief When this is true, the memory allocation tracking is enabled. IMGUI will then tack the numbers of allocations and the number of frees and when
      ///        there is difference between both, IrrIMGUI will throw an assertion during shutdown.
      bool mIsIMGUIMemoryAllocationTrackingEnabled;

      /// @}

      bool operator==(SIMGUISettings const &rCompareSettings)
      {
        bool AreAllSettingsEqual = true;

        AreAllSettingsEqual = AreAllSettingsEqual && (mIsGUIMouseCursorEnabled == rCompareSettings.mIsGUIMouseCursorEnabled);

        return AreAllSettingsEqual;
      }
  };
}

/**
 * @}
 */

#endif /* IRRIMGUI_INCLUDE_IRRIMGUI_SIMGUISETTINGS_H_ */
