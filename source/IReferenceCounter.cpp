/**
 * @file   IReferenceCounter.cpp
 * @author Andre Netzeband
 * @brief  Contains a class to count references.
 * @addtogroup IrrIMGUI
 */

// library includes
#include <IrrIMGUI/IReferenceCounter.h>
#include "private/IrrIMGUIDebug_priv.h"

/**
 * @addtogroup IrrIMGUI
 * @{
 */
namespace IrrIMGUI {
IReferenceCounter::IReferenceCounter(void):
    mReferences(1) {
    return;
}

IReferenceCounter::~IReferenceCounter(void) {
    if(mReferences != 1) {
        LOG_ERROR("An object with counted references is destroyed, but there are still references in use!\n");
        LOG_ERROR(" * object address: " << std::hex << this << "\n");
        LOG_ERROR(" * object references in use: " << std::hex << (mReferences - 1) << "\n");
    }

    return;
}

void IReferenceCounter::grab(void) {
    mReferences++;
    return;
}

void IReferenceCounter::drop(void) {

    if(mReferences == 1) {
        delete this;
    } else {
        mReferences--;
    }

    return;
}

unsigned int IReferenceCounter::getReferenceCount(void) const {
    return mReferences;
}

}

/**
 * @}
 */
