/**
 * @file       CIMGUIEventStorage.h
 * @author     Andre Netzeband
 * @brief      A storage memory to transfer Input-Events from Irrlicht to the IMGUI.
 * @addtogroup IrrIMGUI
 */

#ifndef IRRIMGUI_INCLUDE_IRRIMGUI_CIMGUIEVENTSTORAGE_H_
#define IRRIMGUI_INCLUDE_IRRIMGUI_CIMGUIEVENTSTORAGE_H_

// module includes
#include "CCharFifo.h"
#include "IrrIMGUIConfig.h"

/**
 * @addtogroup IrrIMGUI
 * @{
 */

namespace IrrIMGUI
{
  /// @brief Stores the state of the Keyboard and Mouse input for IMGUI.
  class IRRIMGUI_DLL_API CIMGUIEventStorage
  {
    public:
      /// @brief Standard Constructor to reset all values to 0 and false.
      CIMGUIEventStorage(void):
        mIsLeftMouseButtonPressed(false),
        mIsRightMouseButtonPressed(false),
        mIsMiddleMouseButtonPressed(false),
        mMousePositionX(0),
        mMousePositionY(0),
        mMouseWheelPosition(0.0f),
        mTabPressed(false),
        mLeftPressed(false),
        mRightPressed(false),
        mUpPressed(false),
        mDownPressed(false),
        mPriorPressed(false),
        mNextPressed(false),
        mHomePressed(false),
        mEndPressed(false),
        mDeletePressed(false),
        mBackPressed(false),
        mReturnPressed(false),
        mEscapePressed(false),
        mKeyAPressed(false),
        mKeyCPressed(false),
        mKeyVPressed(false),
        mKeyXPressed(false),
        mKeyYPressed(false),
        mKeyZPressed(false),
        mCtrlPressed(false),
        mShiftPressed(false),
        mAltPressed(false)
      {}

      ///@{
      ///@name Mouse states

      bool mIsLeftMouseButtonPressed;
      bool mIsRightMouseButtonPressed;
      bool mIsMiddleMouseButtonPressed;
      int mMousePositionX;
      int mMousePositionY;
      float mMouseWheelPosition;

      /// @}

      ///@{
      ///@name Special Key states

      bool mTabPressed;
      bool mLeftPressed;
      bool mRightPressed;
      bool mUpPressed;
      bool mDownPressed;
      bool mPriorPressed;
      bool mNextPressed;
      bool mHomePressed;
      bool mEndPressed;
      bool mDeletePressed;
      bool mBackPressed;
      bool mReturnPressed;
      bool mEscapePressed;
      bool mKeyAPressed;
      bool mKeyCPressed;
      bool mKeyVPressed;
      bool mKeyXPressed;
      bool mKeyYPressed;
      bool mKeyZPressed;
      bool mCtrlPressed;
      bool mShiftPressed;
      bool mAltPressed;

      /// @}

      /// @{
      /// @name Memory for all character keys

      CCharFifo mCharFifo;

      /// @}

  };
}

/**
 * @}
 */

#endif /* IRRIMGUI_INCLUDE_IRRIMGUI_CIMGUIEVENTSTORAGE_H_ */
