/**
 * @file   CBasicMemoryLeakDetection.h
 * @author Andre Netzeband
 * @brief  Class for a very basic memory leak detection.
 * @addtogroup IrrIMGUITools
 */

#ifndef LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_TOOLS_CBASICMEMORYLEAKDETECTION_H_
#define LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_TOOLS_CBASICMEMORYLEAKDETECTION_H_

// module includes
#include <IrrIMGUI/IrrIMGUIConfig.h>

#ifdef _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2010_
  #ifdef _DEBUG
    #define _ENABLE_MEMORY_LEAK_DETECTION_
  #endif // _DEBUG
#endif // _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2010_

#ifdef _ENABLE_MEMORY_LEAK_DETECTION_
#include <crtdbg.h>
#endif // _ENABLE_MEMORY_LEAK_DETECTION_

/**
 * @defgroup IrrIMGUITools Tools
 * @ingroup IrrIMGUI
 * @brief Miscellaneous tools, that are not necessarily related to IMGUI or Irrlicht.
 *
 * @{
 */

namespace IrrIMGUI
{
/// @brief Contains definitions for useful tools.
namespace Tools
{
  /**
   * @brief This is a very basic memory leak detection for Windows Systems.
   *
   * @details When creating an object of this class, it will store the current state of the memory.
   *   And when this object is destroyed, it will compare the state of the memory with the stored one.
   *   Thus it can detect differences in memory usage.
   *
   *   It will not show you any more information than just the difference of the both memory states.
   *
   * @attention This class has only a functionality for Windows, compiled with Visual C++. When someone knows how to
   *            perform the same checks with MingW/GCC without using non-standard libraries, please tell me.
   *            For non Windows or Visual C++ compilers the class will compile but it will just do nothing.
   *
   * @code

   #include <IrrIMGUI/Tools/BasicMemoryLeakDetection.h>

   int main(void)
   {
     // just create an object of this class.
     IrrIMGUI::Tools::CBasicMemoryLeakDetection MemoryLeakDetection;

     // ... write your code here ...

     // when the object is destroyed, it will throw automatically an assertion,
     // if there is less memory left than on creation (an indication of a memory leak)
     return 0;
   }

   @endcode
   */
  class IRRIMGUI_DLL_API CBasicMemoryLeakDetection
  {
    public:
      /// @brief Constructor will store the current memory state.
      CBasicMemoryLeakDetection(void);

      /// @brief The Destructor will compare the current memory state with the stored one.
      ~CBasicMemoryLeakDetection(void);

      /// @brief Compares the current memory state with the stored one.
      /// @return Returns the number of bytes that are different between both states (should be 0 when no memory leak occurred).
      int compareMemoryState(void);

      /// @brief Resets the memory state to prepare a new detection.
      void resetMemoryState(void);

    private:
#ifdef _ENABLE_MEMORY_LEAK_DETECTION_
      _CrtMemState mMemoryState;
#endif // _ENABLE_MEMORY_LEAK_DETECTION_
      bool mWasMemoryChecked;
  };

}
}

/**
 * @}
 */


#endif /* LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_TOOLS_CBASICMEMORYLEAKDETECTION_H_ */
