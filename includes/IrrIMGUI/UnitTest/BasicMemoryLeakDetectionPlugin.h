/**
 * @file   BasicMemoryLeakDetectionPlugin.h
 * @author Andre Netzeband
 * @brief  A CppUTest plugin to perform a very basic memory leak detection.
 * @addtogroup IrrIMGUIUTest
 */

#ifndef LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_UNITTEST_BASICMEMORYLEAKDETECTIONPLUGIN_H_
#define LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_UNITTEST_BASICMEMORYLEAKDETECTIONPLUGIN_H_

// library includes
#include <sstream>
#include <IrrIMGUI/UnitTest/IncludeCppUTest.h>

// module includes
#include <IrrIMGUI/Tools/CBasicMemoryLeakDetection.h>

/**
 * @addtogroup IrrIMGUIUTest
 * @{
 */

namespace IrrIMGUI
{
namespace UnitTest
{

  /// @brief This CppUTest plugin performs the basic memory leak detection in every unti test.
  class BasicMemoryLeakDetectionPlugin : public TestPlugin
  {
    public:
      /// @brief Constructor.
      BasicMemoryLeakDetectionPlugin(const SimpleString& name = "BasicMemoryLeakDetection"): TestPlugin(name) { }

      /// @brief Destructor.
      virtual ~BasicMemoryLeakDetectionPlugin() { mMemoryLeakDetection.compareMemoryState(); };

      /// @brief Is performed before every testcase starts.
      virtual void preTestAction(UtestShell &rShell, TestResult &rResult)
      {
        mMemoryLeakDetection.resetMemoryState();
        return;
      }

      /// @brief Is performed after every testcase. It checks, if the memory state difference is 0. If not, it will add an failure to that testcase.
      virtual void postTestAction(UtestShell &rShell, TestResult &rResult)
      {
        if (rResult.getFailureCount() == 0)
        {
          int const MemoryLeak = mMemoryLeakDetection.compareMemoryState();

          if (MemoryLeak != 0)
          {
            std::stringstream ErrorString;
            ErrorString << "Memory Leak detected: " << MemoryLeak << " Bytes are allocated but not freed-up!";

            SimpleString ErrorMessage(ErrorString.str().c_str());
            TestFailure MemoryLeakFailure(&rShell, ErrorMessage);
            rResult.addFailure(MemoryLeakFailure);
          }
        }
        return;
      }

    private:
      IrrIMGUI::Tools::CBasicMemoryLeakDetection mMemoryLeakDetection;
  };


}
}

/**
 * @}
 */


#endif /* LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_UNITTEST_BASICMEMORYLEAKDETECTIONPLUGIN_H_ */
