/**
 * @file   MockHelper.h
 * @author Andre Netzeband
 * @brief  Contains definitions used inside IIMGUIHandleMock, but they must stay independent from the mock, to prevent a too close coupling to the unit test framework from the DLL.
 * @addtogroup IrrIMGUIUTest
 */

#ifndef LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_UNITTEST_MOCKHELPER_H_
#define LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_UNITTEST_MOCKHELPER_H_

// module includes
#include <IrrIMGUI/IrrIMGUIConfig.h>

/**
 * @addtogroup IrrIMGUIUTest
 * @{
 */

namespace IrrIMGUI
{
namespace UnitTest
{
  class IIMGUIHandleMock;

  /// @brief Creates a dummy font in IMGUI to prevent errors for unit-tests that uses the mock.
  IRRIMGUI_DLL_API void createIMGUIDummyFont(void);

  /// @return Returns a dummy texture object for unit-test cases.
  IRRIMGUI_DLL_API IGUITexture * getDummyTexture(void);

  /// @brief This helper class contains definitions, that can not be in IMGUIHandleMock, to prevent tight coupling between DLL and Unit Test Framework.
  class MockHelper
  {
    private:
      friend IIMGUIHandleMock;

      /// @brief If this variable is true, the mock will perform minimal IMGUI calls to not generate an error with IMGUI.
      IRRIMGUI_DLL_API static bool         mIsImGuiActivated;
  };
}
}

/**
 * @}
 */

#endif /* LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_UNITTEST_MOCKHELPER_H_ */
