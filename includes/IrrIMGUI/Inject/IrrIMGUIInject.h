/**
 * @file   IrrIMGUIInject.h
 * @author Andre Netzeband
 * @brief  Functions for dependency injection.
 * @addtogroup IrrIMGUIInject
 */

#ifndef LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_INJECT_IRRIMGUIINJECT_H_
#define LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_INJECT_IRRIMGUIINJECT_H_

// module includes
#include <IrrIMGUI/IrrIMGUI.h>

/**
 * @defgroup IrrIMGUIInject Inject
 * @ingroup IrrIMGUI
 * @brief Definitions for dependency injection.
 *
 * @{
 */

namespace IrrIMGUI
{
/// @brief Contains definitions for Dependency Injection.
namespace Inject
{

  /**
   * @addtogroup IrrIMGUIInject
   * @{
   */

  /// @brief The type of the IMGUI factory function.
  typedef IrrIMGUI::IIMGUIHandle * (IMGUIFactory)(irr::IrrlichtDevice * pDevice, IrrIMGUI::CIMGUIEventStorage * pEventStorage, IrrIMGUI::SIMGUISettings const * pSettings);

  /// @param pFactoryFunction Is a function pointer to the IMGUI factory function to use.
  ///        If it is NULL, it will use the default factory function.
  IRRIMGUI_DLL_API void setIMGUIFactory(IMGUIFactory * pFactoryFunction = nullptr);

  /// @return Returns the current factory function pointer for creating an IMGUI handle instance.
  IRRIMGUI_DLL_API IMGUIFactory * getIMGUIFactory(void);

  /**
   * @}
   */

}
}

/**
 * @}
 */

#endif /* LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_INJECT_IRRIMGUIINJECT_H_ */
