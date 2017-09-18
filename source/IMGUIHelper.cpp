/**
 * @file   IMGUIHelper.cpp
 * @author Andre Netzeband
 * @brief  Contains helper functions for the IMGUI handling.
 * @addtogroup IrrIMGUIPrivate
 */

// library includes
#include <IrrIMGUI/IncludeIrrlicht.h>
#include <IrrIMGUI/IncludeIMGUI.h>
#include <IrrIMGUI/CIMGUIEventStorage.h>
#include <IrrIMGUI/IMGUIHelper.h>
#include "private/CGUITexture.h"

namespace IrrIMGUI {
/// @brief Updates the IMGUI screen size.
/// @param pDevice Is a pointer to an Irrlicht device.
static void updateScreenSize(irr::IrrlichtDevice *const pDevice) {
    ImGuiIO &rGUIIO = ImGui::GetIO();

    irr::core::dimension2d<unsigned int> const &rRenderTargetSize = pDevice->getVideoDriver()->getCurrentRenderTargetSize();
    rGUIIO.DisplaySize = ImVec2(static_cast<float>(rRenderTargetSize.Width), static_cast<float>(rRenderTargetSize.Height));

    return;
}

/// @brief Updated the IMGUI timer.
/// @param pDevice   Is a pointer to an Irrlicht device.
/// @param pLastTime Is a pointer to a variable that stores the timer value from the last update.
static void updateTimer(irr::IrrlichtDevice *const pDevice, float *const pLastTime) {
    ImGuiIO &rGUIIO = ImGui::GetIO();

    float const CurrentTime = static_cast<float>(pDevice->getTimer()->getTime()) / 1000.0f;
    float const DeltaTime   = CurrentTime - *pLastTime;
    *pLastTime = CurrentTime;

    rGUIIO.DeltaTime = ((float)(DeltaTime > 0.0f ? DeltaTime : 0.00001f));

    return;
}

/// @brief Updates the Mouse events from IMGUI.
/// @param pEventStorage Is a pointer to a CIMGUIEventStorage object.
static void updateMouse(CIMGUIEventStorage *const pEventStorage) {
    ImGuiIO &rGUIIO = ImGui::GetIO();

    enum MouseButtons {
        Left   = 0,
        Right  = 1,
        Middle = 2,
    };
    rGUIIO.MousePos          = ImVec2(static_cast<float>(pEventStorage->mMousePositionX), static_cast<float>(pEventStorage->mMousePositionY));
    rGUIIO.MouseDown[Left]   = pEventStorage->mIsLeftMouseButtonPressed;
    rGUIIO.MouseDown[Middle] = pEventStorage->mIsMiddleMouseButtonPressed;
    rGUIIO.MouseDown[Right]  = pEventStorage->mIsRightMouseButtonPressed;
    rGUIIO.MouseWheel        = pEventStorage->mMouseWheelPosition;
    pEventStorage->mMouseWheelPosition = 0.0f;

    return;
}

/// @brief Updates the Keyboard events from IMGUI.
/// @param pEventStorage Is a pointer to a CIMGUIEventStorage object.
static void updateKeyboard(CIMGUIEventStorage *const pEventStorage) {
    ImGuiIO &rGUIIO = ImGui::GetIO();

    rGUIIO.KeysDown[irr::KEY_TAB]    = pEventStorage->mTabPressed;
    rGUIIO.KeysDown[irr::KEY_LEFT]   = pEventStorage->mLeftPressed;
    rGUIIO.KeysDown[irr::KEY_RIGHT]  = pEventStorage->mRightPressed;
    rGUIIO.KeysDown[irr::KEY_UP]     = pEventStorage->mUpPressed;
    rGUIIO.KeysDown[irr::KEY_DOWN]   = pEventStorage->mDownPressed;
    rGUIIO.KeysDown[irr::KEY_PRIOR]  = pEventStorage->mPriorPressed;
    rGUIIO.KeysDown[irr::KEY_NEXT]   = pEventStorage->mNextPressed;
    rGUIIO.KeysDown[irr::KEY_HOME]   = pEventStorage->mHomePressed;
    rGUIIO.KeysDown[irr::KEY_END]    = pEventStorage->mEndPressed;
    rGUIIO.KeysDown[irr::KEY_DELETE] = pEventStorage->mDeletePressed;
    rGUIIO.KeysDown[irr::KEY_BACK]   = pEventStorage->mBackPressed;
    rGUIIO.KeysDown[irr::KEY_RETURN] = pEventStorage->mReturnPressed;
    rGUIIO.KeysDown[irr::KEY_ESCAPE] = pEventStorage->mEscapePressed;
    rGUIIO.KeysDown[irr::KEY_KEY_A]  = pEventStorage->mKeyAPressed;
    rGUIIO.KeysDown[irr::KEY_KEY_C]  = pEventStorage->mKeyCPressed;
    rGUIIO.KeysDown[irr::KEY_KEY_V]  = pEventStorage->mKeyVPressed;
    rGUIIO.KeysDown[irr::KEY_KEY_X]  = pEventStorage->mKeyXPressed;
    rGUIIO.KeysDown[irr::KEY_KEY_Y]  = pEventStorage->mKeyYPressed;
    rGUIIO.KeysDown[irr::KEY_KEY_Z]  = pEventStorage->mKeyZPressed;
    rGUIIO.KeyCtrl                   = pEventStorage->mCtrlPressed;
    rGUIIO.KeyShift                  = pEventStorage->mShiftPressed;
    rGUIIO.KeyAlt                    = pEventStorage->mAltPressed;

    while(!pEventStorage->mCharFifo.isEmpty()) {
        rGUIIO.AddInputCharacter(pEventStorage->mCharFifo.getChar());
    }

    return;
}

void updateIMGUIFrameValues(irr::IrrlichtDevice *const pDevice,  CIMGUIEventStorage *const pEventStorage, float *const pLastTime) {
    updateScreenSize(pDevice);
    updateTimer(pDevice, pLastTime);
    if(pEventStorage) {
        updateMouse(pEventStorage);
        updateKeyboard(pEventStorage);
    }
}

}


