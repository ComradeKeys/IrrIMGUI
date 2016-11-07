/**
 * @file   CGUITexture.cpp
 * @author Andre Netzeband
 * @brief  Contains the class for a GUITexture object.
 * @addtogroup IrrIMGUIPrivate
 */

// module includes
#include "private/CGUITexture.h"

namespace IrrIMGUI {
namespace Private {

CGUITexture::CGUITexture(void):
    mIsUsingOwnMemory(false),
    mSourceType(ETST_UNKNOWN),
    mIsValid(true),
    mGPUTextureID(nullptr) {
    return;
}

CGUITexture::~CGUITexture(void) {
    return;
}

}
}
