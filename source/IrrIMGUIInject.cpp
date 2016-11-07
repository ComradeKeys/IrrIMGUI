/**
 * @file   IrrIMGUIInject.cpp
 * @author Andre Netzeband
 * @brief  Contains function implementation for Dependency Injection.
 * @addtogroup IrrIMGUIInject
 */

// module includes
#include <IrrIMGUI/IrrIMGUI.h>
#include <IrrIMGUI/Inject/IrrIMGUIInject.h>
#include <GL/gl3w.h>
#include "private/IrrIMGUIDebug_priv.h"
#include "CIMGUIHandle.h"
#include "private/IrrIMGUIInject_priv.h"
#include "IrrIMGUI/imgui_irrlicht.h"

namespace IrrIMGUI {
namespace Private {
IIMGUIHandle *createRealIMGUI(irr::IrrlichtDevice *pDevice, CIMGUIEventStorage *pEventStorage, SIMGUISettings const *pSettings) {
    ASSERT(pDevice);

    return new Private::CIMGUIHandle(pDevice, pEventStorage, pSettings);
}
}

namespace Inject {

/// @brief Stores the factory function, that should be used for creating an IIMGUIHandle instances.
static IMGUIFactory *pIMGUIFactoryFunction = IrrIMGUI::Private::createRealIMGUI;


void setIMGUIFactory(IMGUIFactory *pFactoryFunction) {
    if(pFactoryFunction == nullptr) {
        pFactoryFunction = IrrIMGUI::Private::createRealIMGUI;
    }

    pIMGUIFactoryFunction = pFactoryFunction;
    return;
}


IMGUIFactory *getIMGUIFactory(void) {
    return pIMGUIFactoryFunction;
}

}

IIMGUIHandle *createIMGUI(irr::IrrlichtDevice *pDevice, CIMGUIEventStorage *pEventStorage, SIMGUISettings const *pSettings) {
    FASSERT(Inject::pIMGUIFactoryFunction);
    FASSERT(pDevice);
    gl3wInit();
    IIMGUIHandle *handle = Inject::pIMGUIFactoryFunction(pDevice, pEventStorage, pSettings);
    ImGui_ImplIrrlicht_Init(pDevice);
    return handle;
}

}



