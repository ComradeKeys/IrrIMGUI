/**
 * @file   CGUITexture.h
 * @author Andre Netzeband
 * @brief  Contains the class for a GUITexture object.
 * @addtogroup IrrIMGUIPrivate
 */

#ifndef IRRIMGUI_CGUITEXTURE_H_
#define IRRIMGUI_CGUITEXTURE_H_

// library includes
#include <IrrIMGUI/IncludeIrrlicht.h>

// module includes
#include <IrrIMGUI/IGUITexture.h>

/**
 * @addtogroup IrrIMGUIPrivate
 * @{
 */
namespace IrrIMGUI
{
namespace Private
{
  enum TextureSourceType
  {
    ETST_TEXTURE,
    ETST_IMAGE,
    ETST_RAWDATA,
    ETST_GUIFONT,
    ETST_UNKNOWN
  };

  union TextureSource
  {
      irr::video::ITexture *TextureID;
      irr::video::IImage   *ImageID;
      unsigned char              *RawDataID;
      unsigned char              *GUIFontID;
  };

  class CGUITexture : public IGUITexture
  {
    public:
      /// @brief Constructor.
      CGUITexture(void);

      /// @brief Destructor.
      virtual ~CGUITexture(void);

      bool                mIsUsingOwnMemory;
      TextureSourceType   mSourceType;
      TextureSource       mSource;
      bool                mIsValid;
      ImTextureID         mGPUTextureID;

    protected:
  };

}
}

/**
 * @}
 */

#endif  // IRRIMGUI_CGUITEXTURE_H_
