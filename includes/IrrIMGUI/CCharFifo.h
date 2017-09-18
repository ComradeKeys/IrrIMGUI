/**
 * @file   CCharFifo.h
 * @author Andre Netzeband
 * @brief  Class definition for a Fifo Memory
 * @addtogroup IrrIMGUI
 */

#ifndef IRRIMGUI_INCLUDE_IRRIMGUI_CCHARFIFO_H_
#define IRRIMGUI_INCLUDE_IRRIMGUI_CCHARFIFO_H_

// library includes
#include "IncludeIMGUI.h"
#include "IncludeIrrlicht.h"

// module includes
#include "IrrIMGUIConfig.h"

/**
 * @addtogroup IrrIMGUI
 * @{
 */

namespace IrrIMGUI
{
  /// @brief A Fifo Memory to store character inputs from the keyboard.
  class IRRIMGUI_DLL_API CCharFifo
  {
    public:
      /// @{
      /// @name Constructor and Destructor

      /// @brief Standard Constructor
      CCharFifo(void);

      /// @brief Standard Destructor
      ~CCharFifo(void);

      /// @}

      /// @{
      /// @name Write-, Read- and Status-Methods

      /**
       *  @param C Is the input Character to add to the Fifo Memory.
       *  @note  If the Fifo is full an assertion is raised.
       */
      void addChar(ImWchar C);

      /// @return Returns a Character from the Fifo Memory.
      /// @note If the Fifo is empty an assertion is raised.
      ImWchar getChar(void);

      /// @return Returns true, when the Fifo is empty.
      bool isEmpty(void) const;

      /// @return Returns true, when the Fifo is full.
      bool isFull(void) const;

      /// @return Returns the number of characters inside the Fifo.
      unsigned char getNumberOfElements(void) const;

      /// @}

    private:
      ImWchar mCharArray[256];
      unsigned char mWriteIndex;
      unsigned char mReadIndex;
  };
}

/**
 * @}
 */

#endif /* IRRIMGUI_INCLUDE_IRRIMGUI_CCHARFIFO_H_ */
