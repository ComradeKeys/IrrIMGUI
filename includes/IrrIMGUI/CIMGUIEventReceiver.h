/**
 * @file   CIMGUIEventReceiver.h
 * @author Andre Netzeband
 * @brief  Contains a standard Event Receiver for Irrlicht that passed inputs to IMGUI.
 * @addtogroup IrrIMGUI
 */

#ifndef IRRIMGUI_INCLUDE_IRRIMGUI_CIMGUIEVENTRECEIVER_H_
#define IRRIMGUI_INCLUDE_IRRIMGUI_CIMGUIEVENTRECEIVER_H_

// library includes
#include "CIMGUIEventStorage.h"
#include "IncludeIrrlicht.h"

// module includes
#include "IrrIMGUIConfig.h"

/**
 * @addtogroup IrrIMGUI
 * @{
 */

namespace IrrIMGUI
{
  class CIMGUIEventReceiver : public irr::IEventReceiver, public CIMGUIEventStorage
  {
    public:
      /// @brief This function is called by Irrlicht, when an Event occurs.
      /// @param rEvent is a reference to that event.
      /// @return Returns true, if the event has completely been handled by that Receiver.
      bool OnEvent(irr::SEvent const &rEvent)
      {
        bool EventCompletelyHandled = false;

        EventCompletelyHandled = EventCompletelyHandled || checkKeyboardEvents(rEvent);
        EventCompletelyHandled = EventCompletelyHandled || checkMouseEvents(rEvent);

        return EventCompletelyHandled;
      }

    private:
      /// @brief Checks the events that are mouse related.
      /// @param rEvent is a reference to that event.
      /// @return Returns true, if the event has completely been handled by that Receiver.
      bool IRRIMGUI_DLL_API checkMouseEvents(irr::SEvent const &rEvent);

      /// @brief Checks the events that are keyboard related.
      /// @param rEvent is a reference to that event.
      /// @return Returns true, if the event has completely been handled by that Receiver.
      bool IRRIMGUI_DLL_API checkKeyboardEvents(irr::SEvent const &rEvent);

  };
}

/**
 * @}
 */


#endif /* IRRIMGUI_INCLUDE_IRRIMGUI_CIMGUIEVENTRECEIVER_H_ */
