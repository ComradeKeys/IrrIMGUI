/**
 * @file   IGUITexture.h
 * @author Andre Netzeband
 * @brief  Contains an interface to a GUITexture object.
 * @addtogroup IrrIMGUI
 */

#ifndef IRRIMGUI_INCLUDE_IRRIMGUI_IGUITEXTURE_H_
#define IRRIMGUI_INCLUDE_IRRIMGUI_IGUITEXTURE_H_

// library includes
#include "IncludeIMGUI.h"

/**
 * @addtogroup IrrIMGUI
 * @{
 */
namespace IrrIMGUI
{
  class IGUITexture
  {
    public:
      /// @brief Destructor.
      virtual ~IGUITexture(void) {}

      /// @brief Implicit cast operator to ImTextureID.
      operator ImTextureID(void) { return getTextureID(); }

      /// @return Returns the Texture ID.
      virtual ImTextureID getTextureID(void) { return this; }

    protected:
      IGUITexture(void) {};
  };
}

/**
 * @}
 */

#endif  // IRRIMGUI_INCLUDE_IRRIMGUI_IGUITEXTURE_H_
