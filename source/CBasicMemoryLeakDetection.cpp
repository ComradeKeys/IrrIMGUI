/**
 * @file   CBasicMemoryLeakDetection.cpp
 * @author Andre Netzeband
 * @brief  Class for a very basic memory leak detection.
 * @addtogroup IrrIMGUITools
 */

// module includes
#include <IrrIMGUI/Tools/CBasicMemoryLeakDetection.h>
#include "private/IrrIMGUIDebug_priv.h"

namespace IrrIMGUI {
namespace Tools {

CBasicMemoryLeakDetection::CBasicMemoryLeakDetection(void) {
    resetMemoryState();
    return;
}

CBasicMemoryLeakDetection::~CBasicMemoryLeakDetection(void) {
    if(!mWasMemoryChecked) {
        int const MemoryLeak = compareMemoryState();
        if(MemoryLeak != 0) {
            LOG_ERROR("Memory Leak detected: " << MemoryLeak << " Bytes has been allocated but not freed-up!");
        }
    }
    return;
}

int CBasicMemoryLeakDetection::compareMemoryState(void) {
    int MemoryLeak = 0;

#ifdef _ENABLE_MEMORY_LEAK_DETECTION_
    _CrtMemState CurrentMemoryState;
    _CrtMemState MemoryDifference;

    _CrtMemCheckpoint(&CurrentMemoryState);
    _CrtMemDifference(&MemoryDifference, &mMemoryState, &CurrentMemoryState);

    MemoryLeak += static_cast<int>(MemoryDifference.lSizes[_NORMAL_BLOCK]);
    MemoryLeak += static_cast<int>(MemoryDifference.lSizes[_IGNORE_BLOCK]);
    MemoryLeak += static_cast<int>(MemoryDifference.lSizes[_CLIENT_BLOCK]);

    /*
    if (MemoryLeak)
    {
      LOG_WARNING("Detected Memory Leak for _NORMAL_BLOCK: " << std::dec << MemoryDifference.lSizes[_NORMAL_BLOCK] << std::endl);
      LOG_WARNING("Detected Memory Leak for _IGNORE_BLOCK: " << std::dec << MemoryDifference.lSizes[_IGNORE_BLOCK] << std::endl);
      LOG_WARNING("Detected Memory Leak for _CLIENT_BLOCK: " << std::dec << MemoryDifference.lSizes[_CLIENT_BLOCK] << std::endl);
    }
    */

#endif // _ENABLE_MEMORY_LEAK_DETECTION_

    mWasMemoryChecked = true;

    return MemoryLeak;
}

void CBasicMemoryLeakDetection::resetMemoryState(void) {
#ifdef _ENABLE_MEMORY_LEAK_DETECTION_
    _CrtMemCheckpoint(&mMemoryState);
#endif // _ENABLE_MEMORY_LEAK_DETECTION_

    mWasMemoryChecked = false;

    return;
}

}
}


