/**
 * @file   CChannelBuffer.cpp
 * @author Andre Netzeband
 * @brief  Contains the implementation of a channel buffer.
 * @addtogroup IrrIMGUIDebug
 */

// standard library includes
#include <iostream>

// module includes
#include <IrrIMGUI/IrrIMGUIDebug.h>

namespace IrrIMGUI {
namespace Debug {

CChannelBuffer::CChannelBuffer(std::streambuf *pStreamBuffer, char const *pPrefix):
    mpPrefix(pPrefix),
    mpBuffer(pStreamBuffer),
    mIsNewLine(true) {
    return;
}

void CChannelBuffer::setupBuffer(std::streambuf *pStreamBuffer,  bool NextSymbolOnNewLine) {
    mpBuffer = pStreamBuffer;
    mIsNewLine = NextSymbolOnNewLine;
    return;
}

void CChannelBuffer::setupPrefix(char const *pPrefix) {
    mpPrefix = pPrefix;
    return;
}

int CChannelBuffer::overflow(int const Character) {
    int ReturnChar      = Character;

    if(mpBuffer) {
        bool IsPrintAllowed = true;

        if(mIsNewLine) {
            if(!printPrefix()) {
                ReturnChar = EOF;
                IsPrintAllowed = false;
            }
            mIsNewLine = false;
        }

        if(IsPrintAllowed) {
            if(mpBuffer->sputc(Character) == EOF) {
                ReturnChar = EOF;
            }

            if(Character == '\n') {
                mIsNewLine = true;
            }
        }
    }

    return ReturnChar;
}

int CChannelBuffer::sync(void) {
    int Return = 0;

    if(mpBuffer) {
        if(mpBuffer->pubsync() == -1) {
            Return = -1;
        }
    }

    return Return;
}

bool CChannelBuffer::printPrefix(void) {
    bool IsPrintAllowed = true;

    for(int i = 0; mpPrefix[i]; i++) {
        if(mpBuffer->sputc(mpPrefix[i]) == EOF) {
            break;
            IsPrintAllowed = false;
        }
    }

    return IsPrintAllowed;
}

CChannel NoteOutput(std::cout,    "[Note]    ");

CChannel WarningOutput(std::cout, "[Warning] ");

CChannel ErrorOutput(std::cerr,   "[Error]   ");

bool AreUnitTestAssertionsEnabled = true;
}
}

