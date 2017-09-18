/**
 * @file       COpenGLIMGUIDriver.h
 * @author     Andre Netzeband
 * @brief      Contains a driver that uses native OpenGL functions to render the GUI.
 * @attention  This driver is just a test- and fallback implementation. It is not officially supported by the Irrlicht IMGUI binding.
 * @addtogroup IrrIMGUIPrivate
 */

#ifdef _IRRIMGUI_NATIVE_OPENGL_

#ifndef IRRIMGUI_SOURCE_COPENGLIMGUIDRIVER_H_
#define IRRIMGUI_SOURCE_COPENGLIMGUIDRIVER_H_

/**
 * @addtogroup IrrIMGUIPrivate
 * @{
 */

// module includes
#include <IrrIMGUI/IrrIMGUIConfig.h>
#include <IrrIMGUI/IrrIMGUI.h>
#include "IIMGUIDriver.h"

namespace IrrIMGUI {
namespace Private {

/// @brief Contains driver classes for the IMGUI render system.
namespace Driver {

/// @brief A driver that uses native OpenGL functions for rendering.
/// @attention This is a test- and fallback-implementation and is not officially supported by the Irrlicht IMGUI binding.
class COpenGLIMGUIDriver : public IrrIMGUI::Private::IIMGUIDriver {
    friend class IrrIMGUI::Private::IIMGUIDriver;
public:
private:
    /// @{
    /// @name Constructor and Destructor

    /// @brief The constructor.
    /// @param pDevice is a pointer to the Irrlicht Device.
    COpenGLIMGUIDriver(irr::IrrlichtDevice *const pDevice);

    /// @brief The Destructor
    ~COpenGLIMGUIDriver(void);

    /// @}

    /// @{
    /// @name Methods used for setup.

    /// @brief Setups the IMGUI function pointer.
    void setupFunctionPointer(void);

    /// @}

    /// @{
    /// @name Methods used for rendering.

    /// @brief Renders a full IMGUI draw list (called by the IMGUI system).
    /// @param pDrawData is a list of data to draw.
    static void drawGUIList(ImDrawData *pDrawData);

    /// @brief Renders a single command list.
    /// @param pCommandList is the list of commands to render.
    static void drawCommandList(ImDrawList *pCommandList);

    /// @}

    /// @{
    /// @name Image/Texture and Font related methods.

    /// @brief Creates a GUI texture object out of raw data.
    /// @param ColorFormat Is the format of the Color of every Pixel.
    /// @param pPixelData  Is a pointer to the pixel array.
    /// @param Width       Is the number of Pixels in X direction.
    /// @param Height      Is the number of Pixels in Y direction.
    /// @return Returns an GUI texture object.
    virtual IGUITexture *createTexture(EColorFormat ColorFormat, unsigned char *pPixelData, unsigned int Width, unsigned int Height);

    /// @brief Creates a GUI texture object out of an Irrlicht image.
    /// @param pImage Is a pointer to an Irrlicht image object.
    /// @return Returns an GUI texture object.
    virtual IGUITexture *createTexture(irr::video::IImage *pImage);

    /// @brief Creates a GUI texture object out of an Irrlicht texture.
    /// @param pTexture Is a pointer to an Irrlicht texture object.
    /// @return Returns an GUI texture object.
    virtual IGUITexture *createTexture(irr::video::ITexture *pTexture);

    /// @brief Creates a GUI texture out of the currently loaded fonts.
    /// @return Returns an GUI texture object.
    virtual IGUITexture *createFontTexture(void);

    /// @brief Updates a GUI texture object with raw data.
    /// @param pGUITexture Is a pointer to the GUI texture object.
    /// @param ColorFormat Is the format of the Color of every Pixel.
    /// @param pPixelData  Is a pointer to the pixel array.
    /// @param Width       Is the number of Pixels in X direction.
    /// @param Height      Is the number of Pixels in Y direction.
    virtual void updateTexture(IGUITexture *pGUITexture, EColorFormat ColorFormat, unsigned char *pPixelData, unsigned int Width, unsigned int Height);

    /// @brief Updates a GUI texture object with an Irrlicht image.
    /// @param pGUITexture Is a pointer to the GUI texture object.
    /// @param pImage      Is a pointer to an Irrlicht image object.
    virtual void updateTexture(IGUITexture *pGUITexture, irr::video::IImage *pImage);

    /// @brief Updates a GUI texture object with an Irrlicht texture.
    /// @param pGUITexture Is a pointer to the GUI texture object.
    /// @param pTexture    Is a pointer to an Irrlicht image object.
    virtual void updateTexture(IGUITexture *pGUITexture, irr::video::ITexture *pTexture);

    /// @brief Updates a GUI texture with the currently loaded fonts.
    /// @param pGUITexture Is a pointer to the GUI texture object.
    virtual void updateFontTexture(IGUITexture *pGUITexture);

    /**
     * @brief Deletes an texture from graphic memory.
     * @param pGUITexture Is a pointer to the texture to delete. Do not use it afterwards!
     */
    virtual void deleteTexture(IGUITexture *pGUITexture);

    /// @}

};

}
}
}

/**
 * @}
 */


#endif /* IRRIMGUI_SOURCE_COPENGLIMGUIDRIVER_H_ */

#endif // _IRRIMGUI_NATIVE_OPENGL_
