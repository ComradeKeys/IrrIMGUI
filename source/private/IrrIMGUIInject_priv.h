/**
 * @file   IrrIMGUIInject_priv.h
 * @author Andre Netzeband
 * @brief  Private definitions for dependency injection.
 * @addtogroup IrrIMGUIPriv
 */

#ifndef LIBS_IRRIMGUI_SOURCE_PRIVATE_IRRIMGUIINJECT_PRIV_H_
#define LIBS_IRRIMGUI_SOURCE_PRIVATE_IRRIMGUIINJECT_PRIV_H_

// module includes
#include <IrrIMGUI/IrrIMGUI.h>

/**
 * @addtogroup IrrIMGUIPriv
 * @{
 */

namespace IrrIMGUI
{
/// @brief Contains definitions for Dependency Injection.
namespace Private
{

  /// @brief Creates a real IMGUI object (the real factory function for it)
  /// @param pDevice       Is a pointer to an Irrlicht device.
  /// @param pEventStorage Is a pointer to an input event storage.
  /// @param pSettings     Is a pointer to a settings struct to apply.
  /// @return Returns a pointer to an IMGUI handle object.
  IRRIMGUI_DLL_API IIMGUIHandle * createRealIMGUI(irr::IrrlichtDevice * pDevice, CIMGUIEventStorage * pEventStorage, SIMGUISettings const * pSettings);

}
}

/**
 * @}
 */


#endif /* LIBS_IRRIMGUI_SOURCE_PRIVATE_IRRIMGUIINJECT_PRIV_H_ */
