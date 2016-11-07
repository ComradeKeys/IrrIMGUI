/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015-2016 Andre Netzeband based on example OpenGL driver for IMGUI from Omar Cornut
 *
 * The original OpenGL implementation where this driver is based on was implemented
 * by Omar Cornut as an example how to use the IMGUI with OpenGL.
 * You can find the IMGUI here: https://github.com/ocornut/imgui
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/**
 * @file       CIrrlichtIMGUIDriver.cpp
 * @author     Andre Netzeband
 * @brief      Contains a driver that uses Irrlicht primitive drawing functions to render the GUI.
 * @addtogroup IrrIMGUIPrivate
 */

// library includes
#include <IrrIMGUI/IrrIMGUIConfig.h>
#ifdef _IRRIMGUI_WINDOWS_
#include <windows.h>
#endif // _IRRIMGUI_WINDOWS_
#include <GL/gl3w.h>
#include <GL/gl.h>

// module includes
#include "CIrrlichtIMGUIDriver.h"
#include "private/CGUITexture.h"
#include "private/IrrIMGUIDebug_priv.h"
#include "IrrIMGUI/imgui_irrlicht.h"

/**
* @addtogroup IrrIMGUIPrivate
* @{
*/

// Data
static double       g_Time = 0.0f;
static bool         g_MousePressed[3] = { false, false, false };
static float        g_MouseWheel = 0.0f;
static GLuint       g_FontTexture = 0;
static int          g_ShaderHandle = 0, g_VertHandle = 0, g_FragHandle = 0;
static int          g_AttribLocationTex = 0, g_AttribLocationProjMtx = 0, g_AttribLocationClipRect = 0;
static int          g_AttribLocationPosition = 0, g_AttribLocationUV = 0, g_AttribLocationColor = 0;
static unsigned int g_VboHandle = 0, g_VaoHandle = 0, g_ElementsHandle = 0;

namespace IrrIMGUI {
namespace Private {

/// @brief Contains driver classes for the IMGUI render system.
namespace Driver {
/// @brief Functions that help adapting Irrlicht logic to IMGUI
namespace IrrlichtHelper {
/// @brief A magic number for the default font ID IMGUI.
static irr::u8 *const IMGUI_FONT_ID = nullptr;

/// @brief This is used to create an unique texture name.
static irr::u32 TextureCreationID = 0;

/// @brief Indicates, if trilinear filter should be enabled for textures.
static bool IsTrilinearFilterEnabled = false;

/// @brief Translates an IMGUI Color to an Irrlicht Color.
/// @param ImGuiColor is the u32 Color value from IMGUI.
/// @return Returns a SColor object for Irrlicht.
irr::video::SColor getColorFromImGuiColor(irr::u32 ImGuiColor);

/// @brief Creates a Texture object from the currently loaded Fonts.
/// @param pIrrDriver  Is a pointer to the Irrlicht driver object.
/// @return Returns ITexture object as IMGUI Texture ID.
ImTextureID copyTextureIDFromGUIFont(irr::video::IVideoDriver *pIrrDriver);

/// @brief Created a Texture object from raw data.
/// @param pIrrDriver  Is a pointer to the Irrlicht driver object.
/// @param ColorFormat Is the format of the Color of every Pixel.
/// @param pPixelData  Is a pointer to the pixel array.
/// @param Width       Is the number of Pixels in X direction.
/// @param Height      Is the number of Pixels in Y direction.
ImTextureID copyTextureIDFromRawData(irr::video::IVideoDriver *pIrrDriver, EColorFormat ColorFormat, irr::u8 *pPixelData, irr::u32 Width, irr::u32 Height);

/// @brief Creates a Texture object from the currently loaded Fonts.
/// @param pIrrDriver  Is a pointer to the Irrlicht driver object.
/// @param pImage      Is a pointer to an Irrlicht IImage object.
/// @return Returns ITexture object as IMGUI Texture ID.
ImTextureID copyTextureIDFromImage(irr::video::IVideoDriver *pIrrDriver, irr::video::IImage *pImage);

/// @brief Deleted the memory from this texture ID.
/// @param pIrrDriver  Is a pointer to the Irrlicht driver object.
/// @param pGUITexture is a pointer to the texture object.
void deleteTextureID(irr::video::IVideoDriver *pIrrDriver, CGUITexture *pGUITexture);

/// @brief Apples a clipping rectangle. Outside of this rectangle nothing is rendered.
/// @brief Disables the clipping rectangle.
/// @param pIrrDriver    Is a pointer to the Irrlicht driver object.
void disableClippingRect(irr::video::IVideoDriver *pIrrDriver);
}

irr::core::vector3df CIrrlichtIMGUIDriver::mOffset(0.0f, 0.0f, 0.0f);

CIrrlichtIMGUIDriver::CIrrlichtIMGUIDriver(irr::IrrlichtDevice *const pDevice):
    IIMGUIDriver(pDevice) {
    setupFunctionPointer();

    irr::video::IVideoDriver *pDriver = pDevice->getVideoDriver();
    irr::video::E_DRIVER_TYPE Type = pDriver->getDriverType();

    switch(Type) {
        case irr::video::EDT_OPENGL:
            mOffset = irr::core::vector3df(-0.375f, -0.375f, 0.0f);
            IrrlichtHelper::IsTrilinearFilterEnabled = false;
            LOG_NOTE("{IrrIMGUI-Irr} Start Irrlicht High Level GUI renderer in OpenGL mode.\n");
            break;

        case irr::video::EDT_NULL:
            mOffset = irr::core::vector3df(0.0f, 0.0f, 0.0f);
            IrrlichtHelper::IsTrilinearFilterEnabled = false;
            break;

        default:
            mOffset = irr::core::vector3df(0.0f, 0.0f, 0.0f);
            LOG_WARNING("{IrrIMGUI-Irr} Start Irrlicht High Level GUI renderer in unknown video mode, this Irrlicht renderer might not be supported!\n");
            break;
    }


    return;
}

CIrrlichtIMGUIDriver::~CIrrlichtIMGUIDriver(void) {
    return;
}

void CIrrlichtIMGUIDriver::setupFunctionPointer(void) {
    ImGuiIO &rGUIIO  = ImGui::GetIO();

    rGUIIO.RenderDrawListsFn = CIrrlichtIMGUIDriver::drawGUIList;
puts("Better draw function has been set");
    return;
}

void CIrrlichtIMGUIDriver::drawGUIList(ImDrawData *pDrawData) {
    puts("Better draw list being called");
    // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
    ImGuiIO &io = ImGui::GetIO();
    int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
    int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
    if(fb_width == 0 || fb_height == 0) {
        return;
    }
    pDrawData->ScaleClipRects(io.DisplayFramebufferScale);
    // Backup GL state
    GLint last_program;
    glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
    GLint last_texture;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
    GLint last_active_texture;
    glGetIntegerv(GL_ACTIVE_TEXTURE, &last_active_texture);
    GLint last_array_buffer;
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
    GLint last_element_array_buffer;
    glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &last_element_array_buffer);
    GLint last_vertex_array;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);
    GLint last_blend_src;
    glGetIntegerv(GL_BLEND_SRC, &last_blend_src);
    GLint last_blend_dst;
    glGetIntegerv(GL_BLEND_DST, &last_blend_dst);
    GLint last_blend_equation_rgb;
    glGetIntegerv(GL_BLEND_EQUATION_RGB, &last_blend_equation_rgb);
    GLint last_blend_equation_alpha;
    glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &last_blend_equation_alpha);
    GLint last_viewport[4];
    glGetIntegerv(GL_VIEWPORT, last_viewport);
    GLint last_scissor_box[4];
    glGetIntegerv(GL_SCISSOR_BOX, last_scissor_box);
    GLboolean last_enable_blend = glIsEnabled(GL_BLEND);
    GLboolean last_enable_cull_face = glIsEnabled(GL_CULL_FACE);
    GLboolean last_enable_depth_test = glIsEnabled(GL_DEPTH_TEST);
    GLboolean last_enable_scissor_test = glIsEnabled(GL_SCISSOR_TEST);
    
    // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glActiveTexture(GL_TEXTURE0);
    
    // Setup orthographic projection matrix
    glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);
    const float ortho_projection[4][4] = {
        { 2.0f / io.DisplaySize.x, 0.0f,                   0.0f, 0.0f },
        { 0.0f,                  2.0f / -io.DisplaySize.y, 0.0f, 0.0f },
        { 0.0f,                  0.0f,                  -1.0f, 0.0f },
        { -1.0f,                  1.0f,                   0.0f, 1.0f },
    };
    glUseProgram(g_ShaderHandle);
    glUniform1i(g_AttribLocationTex, 0);
    glUniformMatrix4fv(g_AttribLocationProjMtx, 1, GL_FALSE, &ortho_projection[0][0]);
    glBindVertexArray(g_VaoHandle);
    
    for(int n = 0; n < pDrawData->CmdListsCount; n++) {
        const ImDrawList *cmd_list = pDrawData->CmdLists[n];
        const ImDrawIdx *idx_buffer_offset = 0;
        
        glBindBuffer(GL_ARRAY_BUFFER, g_VboHandle);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)cmd_list->VtxBuffer.Size * sizeof(ImDrawVert), (GLvoid *)cmd_list->VtxBuffer.Data, GL_STREAM_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ElementsHandle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx), (GLvoid *)cmd_list->IdxBuffer.Data, GL_STREAM_DRAW);
        
        for(int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++) {
            const ImDrawCmd *pcmd = &cmd_list->CmdBuffer[cmd_i];
            if(pcmd->UserCallback) {
                pcmd->UserCallback(cmd_list, pcmd);
            } else {
                glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
                //                glScissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
                float clipRect[4];
                clipRect[0] = (int)pcmd->ClipRect.x;
                clipRect[1] = (int)(fb_height - pcmd->ClipRect.w);
                clipRect[2] = (int)(pcmd->ClipRect.z - pcmd->ClipRect.x);
                clipRect[3] = (int)(pcmd->ClipRect.w - pcmd->ClipRect.y);
                glUniform4f(g_AttribLocationClipRect, clipRect[0], clipRect[1], clipRect[2], clipRect[3]);
                
                glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer_offset);
            }
            idx_buffer_offset += pcmd->ElemCount;
        }
    }
    
    // Restore modified GL state
    glUseProgram(last_program);
    glActiveTexture(last_active_texture);
    glBindTexture(GL_TEXTURE_2D, last_texture);
    glBindVertexArray(last_vertex_array);
    glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, last_element_array_buffer);
    glBlendEquationSeparate(last_blend_equation_rgb, last_blend_equation_alpha);
    glBlendFunc(last_blend_src, last_blend_dst);
    if(last_enable_blend) {
        glEnable(GL_BLEND);
    } else {
        glDisable(GL_BLEND);
    }
    if(last_enable_cull_face) {
        glEnable(GL_CULL_FACE);
    } else {
        glDisable(GL_CULL_FACE);
    }
    if(last_enable_depth_test) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
    //    if (last_enable_scissor_test) glEnable(GL_SCISSOR_TEST); else glDisable(GL_SCISSOR_TEST);
    glEnable(GL_CLIP_DISTANCE0);
    glEnable(GL_CLIP_DISTANCE1);
    glEnable(GL_CLIP_DISTANCE2);
    glEnable(GL_CLIP_DISTANCE3);
    glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
    //    glScissor(last_scissor_box[0], last_scissor_box[1], (GLsizei)last_scissor_box[2], (GLsizei)last_scissor_box[3]);
    glDisable(GL_CLIP_DISTANCE3);
    glDisable(GL_CLIP_DISTANCE2);
    glDisable(GL_CLIP_DISTANCE1);
    glDisable(GL_CLIP_DISTANCE0);

}

void CIrrlichtIMGUIDriver::drawCommandList(ImDrawList *pCommandList) {
    // Implemented in the new version
    return;
}

IGUITexture *CIrrlichtIMGUIDriver::createTexture(EColorFormat const ColorFormat, irr::u8 *const pPixelData, irr::u32 const Width, irr::u32 const Height) {
    mTextureInstances++;
    CGUITexture *const pGUITexture = new CGUITexture();

    pGUITexture->mIsUsingOwnMemory = true;
    pGUITexture->mSourceType       = ETST_RAWDATA;
    pGUITexture->mSource.RawDataID = pPixelData;
    pGUITexture->mIsValid          = true;
    pGUITexture->mGPUTextureID     = IrrlichtHelper::copyTextureIDFromRawData(getIrrDevice()->getVideoDriver(), ColorFormat, pPixelData, Width, Height);

    return pGUITexture;
}

IGUITexture *CIrrlichtIMGUIDriver::createTexture(irr::video::IImage *const pImage) {
    mTextureInstances++;
    CGUITexture *const pGUITexture = new CGUITexture();

    pGUITexture->mIsUsingOwnMemory = true;
    pGUITexture->mSourceType       = ETST_IMAGE;
    pGUITexture->mSource.ImageID   = pImage;
    pGUITexture->mIsValid          = true;
    pGUITexture->mGPUTextureID     = IrrlichtHelper::copyTextureIDFromImage(getIrrDevice()->getVideoDriver(), pImage);

    return pGUITexture;
}

IGUITexture *CIrrlichtIMGUIDriver::createTexture(irr::video::ITexture *pTexture) {
    mTextureInstances++;
    CGUITexture *const pGUITexture = new CGUITexture();

    pGUITexture->mIsUsingOwnMemory = false;
    pGUITexture->mSourceType       = ETST_TEXTURE;
    pGUITexture->mSource.TextureID = pTexture;
    pGUITexture->mIsValid          = true;
    pGUITexture->mGPUTextureID     = static_cast<ImTextureID>(static_cast<void *const>(pTexture));

    return pGUITexture;
}

IGUITexture *CIrrlichtIMGUIDriver::createFontTexture(void) {
    mTextureInstances++;
    CGUITexture *const pGUITexture = new CGUITexture();

    pGUITexture->mIsUsingOwnMemory = true;
    pGUITexture->mSourceType       = ETST_GUIFONT;
    pGUITexture->mSource.GUIFontID = IrrlichtHelper::IMGUI_FONT_ID;
    pGUITexture->mIsValid          = true;
    pGUITexture->mGPUTextureID     = IrrlichtHelper::copyTextureIDFromGUIFont(getIrrDevice()->getVideoDriver());

    void *const pFontTexture = reinterpret_cast<void *>(pGUITexture);
    ImGui::GetIO().Fonts->TexID = pFontTexture;

    return pGUITexture;
}

void CIrrlichtIMGUIDriver::updateTexture(IGUITexture *const pGUITexture, EColorFormat const ColorFormat, irr::u8 *const pPixelData, irr::u32 const Width, irr::u32 const Height) {
    CGUITexture *const pRealTexture = dynamic_cast<CGUITexture *const>(pGUITexture);
    bool IsRecreationNecessary = false;

    FASSERT(pRealTexture->mIsValid);

    if(pRealTexture->mIsUsingOwnMemory) {
        IsRecreationNecessary = true;
    } else if(pRealTexture->mSourceType != ETST_RAWDATA) {
        IsRecreationNecessary = true;
    } else if(pRealTexture->mSource.RawDataID != pPixelData) {
        IsRecreationNecessary = true;
    }

    if(IsRecreationNecessary) {
        IrrlichtHelper::deleteTextureID(getIrrDevice()->getVideoDriver(), pRealTexture);

        pRealTexture->mIsUsingOwnMemory = true;
        pRealTexture->mSourceType       = ETST_RAWDATA;
        pRealTexture->mSource.RawDataID = pPixelData;
        pRealTexture->mIsValid          = true;
        pRealTexture->mGPUTextureID     = IrrlichtHelper::copyTextureIDFromRawData(getIrrDevice()->getVideoDriver(), ColorFormat, pPixelData, Width, Height);
    }

    return;
}

void CIrrlichtIMGUIDriver::updateTexture(IGUITexture *const pGUITexture, irr::video::IImage *const pImage) {
    CGUITexture *const pRealTexture = dynamic_cast<CGUITexture *const>(pGUITexture);
    bool IsRecreationNecessary = false;

    FASSERT(pRealTexture->mIsValid);

    if(pRealTexture->mIsUsingOwnMemory) {
        IsRecreationNecessary = true;
    } else if(pRealTexture->mSourceType != ETST_IMAGE) {
        IsRecreationNecessary = true;
    } else if(pRealTexture->mSource.ImageID != pImage) {
        IsRecreationNecessary = true;
    }

    if(IsRecreationNecessary) {
        IrrlichtHelper::deleteTextureID(getIrrDevice()->getVideoDriver(), pRealTexture);

        pRealTexture->mIsUsingOwnMemory = true;
        pRealTexture->mSourceType       = ETST_IMAGE;
        pRealTexture->mSource.ImageID   = pImage;
        pRealTexture->mIsValid          = true;
        pRealTexture->mGPUTextureID     = IrrlichtHelper::copyTextureIDFromImage(getIrrDevice()->getVideoDriver(), pImage);
    }

    return;
}

void CIrrlichtIMGUIDriver::updateTexture(IGUITexture *const pGUITexture, irr::video::ITexture *const pTexture) {
    CGUITexture *const pRealTexture = dynamic_cast<CGUITexture *const>(pGUITexture);
    bool IsRecreationNecessary = false;

    FASSERT(pRealTexture->mIsValid);

    if(pRealTexture->mIsUsingOwnMemory) {
        IsRecreationNecessary = true;
    } else if(pRealTexture->mSourceType != ETST_TEXTURE) {
        IsRecreationNecessary = true;
    } else if(pRealTexture->mSource.TextureID != pTexture) {
        IsRecreationNecessary = true;
    }

    if(IsRecreationNecessary) {
        IrrlichtHelper::deleteTextureID(getIrrDevice()->getVideoDriver(), pRealTexture);

        pRealTexture->mIsUsingOwnMemory = false;
        pRealTexture->mSourceType       = ETST_TEXTURE;
        pRealTexture->mSource.TextureID = pTexture;
        pRealTexture->mIsValid          = true;
        pRealTexture->mGPUTextureID     = static_cast<ImTextureID>(static_cast<void *const>(pTexture));
    }

    return;
}

void CIrrlichtIMGUIDriver::updateFontTexture(IGUITexture *const pGUITexture) {
    CGUITexture *const pRealTexture = dynamic_cast<CGUITexture *const>(pGUITexture);
    bool IsRecreationNecessary = false;

    FASSERT(pRealTexture->mIsValid);

    if(pRealTexture->mIsUsingOwnMemory) {
        IsRecreationNecessary = true;
    } else if(pRealTexture->mSourceType != ETST_GUIFONT) {
        IsRecreationNecessary = true;
    } else if(pRealTexture->mSource.GUIFontID != IrrlichtHelper::IMGUI_FONT_ID) {
        IsRecreationNecessary = true;
    }

    if(IsRecreationNecessary) {
        IrrlichtHelper::deleteTextureID(getIrrDevice()->getVideoDriver(), pRealTexture);

        pRealTexture->mIsUsingOwnMemory = true;
        pRealTexture->mSourceType       = ETST_GUIFONT;
        pRealTexture->mSource.GUIFontID = IrrlichtHelper::IMGUI_FONT_ID;
        pRealTexture->mIsValid          = true;
        pRealTexture->mGPUTextureID     = IrrlichtHelper::copyTextureIDFromGUIFont(getIrrDevice()->getVideoDriver());

        void *const pFontTexture = reinterpret_cast<void *>(pGUITexture);
        ImGui::GetIO().Fonts->TexID = pFontTexture;
    }

    return;
}

void CIrrlichtIMGUIDriver::deleteTexture(IGUITexture *const pGUITexture) {
    CGUITexture *const pRealTexture = dynamic_cast<CGUITexture *const>(pGUITexture);

    FASSERT(pRealTexture->mIsValid);

    IrrlichtHelper::deleteTextureID(getIrrDevice()->getVideoDriver(), pRealTexture);
    delete pRealTexture;

    mTextureInstances--;
    return;
}


namespace IrrlichtHelper {


irr::video::SColor getColorFromImGuiColor(irr::u32 const ImGuiColor) {
    ImColor const Color(ImGuiColor);

    irr::u8 const Red   = static_cast<irr::u8>(Color.Value.x * 255);
    irr::u8 const Green = static_cast<irr::u8>(Color.Value.y * 255);
    irr::u8 const Blue  = static_cast<irr::u8>(Color.Value.z * 255);
    irr::u8 const Alpha = static_cast<irr::u8>(Color.Value.w * 255);

    return irr::video::SColor(Alpha, Red, Green, Blue);
}

ImTextureID copyTextureIDFromRawData(irr::video::IVideoDriver *const pIrrDriver, EColorFormat const ColorFormat, irr::u8 *const pPixelData, irr::u32 const Width, irr::u32 const Height) {

    irr::u32 *pImageData = nullptr;
    bool IsTempMemoryUsed = false;

    // decide if we need to translate the color or not
    switch(ColorFormat) {
        case ECF_A8R8G8B8:
            pImageData       = reinterpret_cast<irr::u32 *>(pPixelData);
            IsTempMemoryUsed = false;
            break;

        case ECF_R8G8B8A8:
            pImageData       = reinterpret_cast<irr::u32 *>(pPixelData);
            IsTempMemoryUsed = false;

            for(irr::u32 X = 0; X < (Width * Height); X++) {
                irr::video::SColor Color = getColorFromImGuiColor(pImageData[X]);
                Color.getData(&pImageData[X], irr::video::ECF_A8R8G8B8);
            }

            break;

        case ECF_A8:
            pImageData       = new irr::u32[Width * Height];
            IsTempMemoryUsed = true;

            for(irr::u32 X = 0; X < (Width * Height); X++) {
                // set only Alpha
                irr::video::SColor Color(pPixelData[X], 255, 255, 255);
                Color.getData(&pImageData[X], irr::video::ECF_A8R8G8B8);
            }

            break;

        default:
            LOG_ERROR("Unknown ColorFormat " << ColorFormat << "!\n");
            FASSERT(false);
            break;
    }

    // do not generate mipmaps for font textures
    pIrrDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);

    // create image object from raw data
    irr::core::dimension2d<irr::u32> const Size(Width, Height);
    irr::video::IImage *const pImage = pIrrDriver->createImageFromData(irr::video::ECF_A8R8G8B8, Size, pImageData);

    // create unique texture name for Irrlicht
    irr::io::path const TextureName = "IrrIMGUIRaw" + TextureCreationID;
    TextureCreationID++;

    // create texture object
    irr::video::ITexture *const pTexture = pIrrDriver->addTexture(TextureName, pImage);
    ImTextureID const TextureID = static_cast<ImTextureID>(static_cast<void *const>(pTexture));

    pIrrDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);

    // delete image object
    pImage->drop();

    if(IsTempMemoryUsed) {
        delete[] pImageData;
    }

    LOG_NOTE("{IrrIMGUI-Irr} Create ITexture object from Raw Data. Handle: " << std::hex << TextureID << "\n");

    return TextureID;
}

ImTextureID copyTextureIDFromGUIFont(irr::video::IVideoDriver *const pIrrDriver) {
    // Get Font Texture from IMGUI system.
    irr::u8 *pPixelData;
    int Width, Height;
    ImGui::GetIO().Fonts->GetTexDataAsAlpha8(&pPixelData, &Width, &Height);

    ImTextureID const FontTexture = copyTextureIDFromRawData(pIrrDriver, ECF_A8, pPixelData, Width, Height);

    // delete temporary texture memory in IMGUI
    ImGui::GetIO().Fonts->ClearTexData();

    return FontTexture;
}

ImTextureID copyTextureIDFromImage(irr::video::IVideoDriver *const pIrrDriver, irr::video::IImage *const pImage) {
    // do not generate mipmaps for font textures
    pIrrDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);

    // create unique texture name for Irrlicht
    irr::io::path const TextureName = "IrrIMGUIImage" + TextureCreationID;
    TextureCreationID++;

    // create texture object
    irr::video::ITexture *const pTexture = pIrrDriver->addTexture(TextureName, pImage);
    ImTextureID const TextureID = static_cast<ImTextureID>(static_cast<void *const>(pTexture));

    pIrrDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);

    return TextureID;
}

void deleteTextureID(irr::video::IVideoDriver *const pIrrDriver, CGUITexture *const pGUITexture) {
    if(pGUITexture->mIsUsingOwnMemory) {
        LOG_NOTE("{IrrIMGUI-Irr} Delete ITexture memory. Handle: " << std::hex << pGUITexture->mGPUTextureID << "\n");
        irr::video::ITexture *const pIrrlichtTexture = reinterpret_cast<irr::video::ITexture *const>(pGUITexture->mGPUTextureID);

        pIrrDriver->removeTexture(pIrrlichtTexture);

        pGUITexture->mIsUsingOwnMemory = false;
        pGUITexture->mGPUTextureID = nullptr;
    }

    pGUITexture->mIsValid = false;
    pGUITexture->mSourceType = ETST_UNKNOWN;

    return;
}

void disableClippingRect(irr::video::IVideoDriver *const pIrrDriver) {
    pIrrDriver->enableClipPlane(0, false);
    pIrrDriver->enableClipPlane(1, false);
    pIrrDriver->enableClipPlane(2, false);
    pIrrDriver->enableClipPlane(3, false);

    return;
}
}
}
}
}

/**
 * @}
 */

