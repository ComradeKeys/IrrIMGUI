/**
 * @file   CCharFifo.cpp
 * @author Andre Netzeband
 * @brief  Class definition for a Fifo Memory
 * @addtogroup IrrIMGUI
 */

// module includes
#include <IrrIMGUI/IrrIMGUI.h>
#include "private/IrrIMGUIDebug_priv.h"

#define STATIC_ARRAY_SIZE(ARRAY) (sizeof(ARRAY)/sizeof(ARRAY[0]))     // TODO: maybe use a template for the type

/**
 * @addtogroup IrrIMGUI
 * @{
 */

namespace IrrIMGUI {
CCharFifo::CCharFifo(void):
    mWriteIndex(0),
    mReadIndex(0) {

    ASSERT(isEmpty() == true);
    ASSERT(isFull() == false);

    return;
}

CCharFifo::~CCharFifo(void) {
    return;
}

void CCharFifo::addChar(ImWchar C) {
    if(!isFull()) {
        ASSERT(mWriteIndex < STATIC_ARRAY_SIZE(mCharArray));

        mCharArray[mWriteIndex] = C;
        mWriteIndex++;
    }

    ASSERT(isEmpty() == false);

    return;
}

ImWchar CCharFifo::getChar(void) {
    ImWchar ReturnChar = 0;

    if(!isEmpty()) {
        ASSERT(mReadIndex < STATIC_ARRAY_SIZE(mCharArray));

        ReturnChar = mCharArray[mReadIndex];
        mReadIndex++;
    } else {
        FASSERT(false);
    }

    ASSERT(isFull() == false);

    return ReturnChar;
}

bool CCharFifo::isEmpty(void) const {
    return mWriteIndex == mReadIndex;
}

bool CCharFifo::isFull(void) const {
    return static_cast<unsigned char>(mWriteIndex + 1) == mReadIndex;
}

unsigned char CCharFifo::getNumberOfElements(void) const {
    return mWriteIndex - mReadIndex;
}

}

/**
 * @}
 */



