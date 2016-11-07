/**
 * @file   UnitTest.cpp
 * @author Andre Netzeband
 * @brief  Contains helper functions for the unit testing.
 * @addtogroup IrrIMGUIPrivate
 */


// library includes
#include <IrrIMGUI/IncludeIrrlicht.h>
#include <IrrIMGUI/IncludeIMGUI.h>
#include <IrrIMGUI/CIMGUIEventStorage.h>
#include "private/CGUITexture.h"
#include <IrrIMGUI/UnitTest/MockHelper.h>

namespace IrrIMGUI {
namespace UnitTest {

void createIMGUIDummyFont(void) {
    ImGuiIO &rGUIIO = ImGui::GetIO();

    unsigned char *pPixelData;
    int Width;
    int Height;
    int BytePerPixel;
    rGUIIO.Fonts->GetTexDataAsRGBA32(&pPixelData, &Width, &Height, &BytePerPixel);

    return;
}

IGUITexture *getDummyTexture(void) {
    static Private::CGUITexture DummyTexture;
    return &DummyTexture;
}

bool MockHelper::mIsImGuiActivated = true;

}
}
