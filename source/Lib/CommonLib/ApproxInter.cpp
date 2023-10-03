#include "ApproxInter.h"

BufferRange::BufferRange(uint8_t * const initialAddress, uint8_t const * const finalAddress) : m_initialAddress(initialAddress), m_finalAddress(finalAddress) {}

//double ApproxInter::MEReadBER;
//double ApproxInter::MEWriteBER;

/*unsigned ApproxInter::frameBufferWidth, ApproxInter::frameBufferHeight;
unsigned ApproxInter::xMargin, ApproxInter::yMargin;

bool ApproxInter::collectBufferSize, ApproxInter::tmpBool;

int ApproxInter::debugEnable;

std::fstream ApproxInter::fp;

void ApproxInter::init() {
    //MEReadBER = 0.0;
    //MEWriteBER = 0.0;
    collectBufferSize = true;
    tmpBool = false;
}

void ApproxInter::initDebug() {
    if(debugEnable) {
        fp.open("debug.txt", std::fstream::out);
    }
}*/