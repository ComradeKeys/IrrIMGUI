/**
 * @file   CIMGUIHandle.cpp
 * @author Andre Netzeband
 * @brief  Contains a handle to setup the IMGUI for Irrlicht.
 * @addtogroup IrrIMGUIPrivate
 */

// library includes
#include <IrrIMGUI/IrrIMGUI.h>
#include "CIMGUIHandle.h"
#include "IIMGUIDriver.h"
#include <IrrIMGUI/IMGUIHelper.h>
#include "private/IrrIMGUIDebug_priv.h"
#include "IrrIMGUI/imgui_irrlicht.h"
#include <GL/gl3w.h>
/**
 * @addtogroup IrrIMGUIPrivate
 * @{
 */

namespace IrrIMGUI {
namespace Private {
irr::u32 CIMGUIHandle::mHandleInstances = 0;

CIMGUIHandle::CIMGUIHandle(irr::IrrlichtDevice *const pDevice, CIMGUIEventStorage *const pEventStorage, SIMGUISettings const &rSettings):
    CIMGUIHandle(pDevice, pEventStorage, &rSettings) {
    return;
}

CIMGUIHandle::CIMGUIHandle(irr::IrrlichtDevice *const pDevice, CIMGUIEventStorage *const pEventStorage, SIMGUISettings const *const pSettings) {
    mpGUIDriver = IIMGUIDriver::getInstance(pDevice);
    mLastTime    = static_cast<float>(pDevice->getTimer()->getTime()) / 1000.0f;
    mpEventStorage = pEventStorage;
    mHandleInstances++;

    if(pSettings) {
        mpGUIDriver->setSettings(*pSettings);
    }

    return;
}

CIMGUIHandle::~CIMGUIHandle(void) {
    irr::IrrlichtDevice *const pIrrDevice = mpGUIDriver->getIrrDevice();

    if(mHandleInstances == 0) {
        LOG_ERROR("The number of CIMGUIHandle instances is out of sync (" << mHandleInstances << " instances)!");
    } else {
        mHandleInstances--;

        if(mHandleInstances == 0) {
            IIMGUIDriver::deleteInstance();
        }
    }

    return;
}

void CIMGUIHandle::drawAll(void) {
    glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);

    ImGui::Render();
    return;
}

void CIMGUIHandle::startGUI(void) {

    updateIMGUIFrameValues(mpGUIDriver->getIrrDevice(), mpEventStorage, &mLastTime);
    ImGui_ImplIrrlicht_NewFrame(mpGUIDriver->getIrrDevice());
    
    // start new GUI frame
  //  ImGui::NewFrame();

    return;
}

SIMGUISettings const &CIMGUIHandle::getSettings(void) const {
    return mpGUIDriver->getSettings();
}

void CIMGUIHandle::setSettings(SIMGUISettings const &rSettings) {
    mpGUIDriver->setSettings(rSettings);
}

ImFont *CIMGUIHandle::addFont(ImFontConfig const *const pFontConfig) {
    return ImGui::GetIO().Fonts->AddFont(pFontConfig);
}

ImFont *CIMGUIHandle::addDefaultFont(ImFontConfig const *const pFontConfig) {
    return ImGui::GetIO().Fonts->AddFontDefault(pFontConfig);
}

ImFont *CIMGUIHandle::addFontFromFileTTF(char const *const pFileName, float const FontSizeInPixel, ImFontConfig const *const pFontConfig, ImWchar const *const pGlyphRanges) {
    return ImGui::GetIO().Fonts->AddFontFromFileTTF(pFileName, FontSizeInPixel, pFontConfig, pGlyphRanges);
}

ImFont *CIMGUIHandle::addFontFromMemoryTTF(void *const pTTFData, int const TTFSize, float const FontSizeInPixel, ImFontConfig const *const pFontConfig, ImWchar const *const pGlyphRanges) {
    return ImGui::GetIO().Fonts->AddFontFromMemoryTTF(pTTFData, TTFSize, FontSizeInPixel, pFontConfig, pGlyphRanges);
}

ImFont *CIMGUIHandle::addFontFromMemoryCompressedTTF(void const *const pCompressedTTFData, int const CompressedTTFSize, float const FontSizeInPixel, ImFontConfig const *const pFontConfig, ImWchar const *const pGlyphRanges) {
    return ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(pCompressedTTFData, CompressedTTFSize, FontSizeInPixel, pFontConfig, pGlyphRanges);
}

ImFont *CIMGUIHandle::addFontFromMemoryCompressedBase85TTF(char const *const pCompressedTTFDataBase85, float const FontSizeInPixel, ImFontConfig const *const pFontConfig, const ImWchar *const pGlyphRanges) {
    return ImGui::GetIO().Fonts->AddFontFromMemoryCompressedBase85TTF(pCompressedTTFDataBase85, FontSizeInPixel, pFontConfig, pGlyphRanges);
}

void CIMGUIHandle::compileFonts(void) {
    mpGUIDriver->compileFonts();
    return;
}

void CIMGUIHandle::resetFonts(void) {
    ImGui::GetIO().Fonts->Clear();
    addDefaultFont();
    mpGUIDriver->compileFonts();
    return;
}

ImWchar const *CIMGUIHandle::getGlyphRangesDefault(void) {
    return ImGui::GetIO().Fonts->GetGlyphRangesDefault();
}

ImWchar const *CIMGUIHandle::getGlyphRangesJapanese(void) {
    return ImGui::GetIO().Fonts->GetGlyphRangesJapanese();
}

ImWchar const *CIMGUIHandle::getGlyphRangesChinese(void) {
    return ImGui::GetIO().Fonts->GetGlyphRangesChinese();
}

ImWchar const *CIMGUIHandle::getGlyphRangesCyrillic(void) {
    return ImGui::GetIO().Fonts->GetGlyphRangesCyrillic();
}

IGUITexture *CIMGUIHandle::createTexture(irr::video::IImage *pImage) {
    return mpGUIDriver->createTexture(pImage);
}

IGUITexture *CIMGUIHandle::createTexture(irr::video::ITexture *pTexture) {
    return mpGUIDriver->createTexture(pTexture);
}

void CIMGUIHandle::updateTexture(IGUITexture *pGUITexture, irr::video::IImage *pImage) {
    mpGUIDriver->updateTexture(pGUITexture, pImage);
    return;
}

void CIMGUIHandle::updateTexture(IGUITexture *pGUITexture, irr::video::ITexture *pTexture) {
    mpGUIDriver->updateTexture(pGUITexture, pTexture);
    return;
}

void CIMGUIHandle::deleteTexture(IGUITexture *pGUITexture) {
    mpGUIDriver->deleteTexture(pGUITexture);
    return;
}


}
}

/**
 * @}
 */

