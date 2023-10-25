#include "ApproxInter.h"

BufferRange::BufferRange(uint8_t * const initialAddress, uint8_t const * const finalAddress) : m_initialAddress(initialAddress), m_finalAddress(finalAddress) {}

AllocatedBuffersSet ApproxInter::allocatedBuffers{};

void ApproxInter::MarkBuffer(const BufferRange& toMark) {
	ApproxInter::allocatedBuffers.insert(toMark);
}

void ApproxInter::UnmarkBuffer(const BufferRange& toUnmark) {
	ApproxInter::allocatedBuffers.erase(toUnmark);
}

void ApproxInter::UnmarkBuffer(void const * const address) {
	ApproxInter::UnmarkBuffer(BufferRange((uint8_t*) address, ((uint8_t*) address) + 1));
}

void ApproxInter::InstrumentIfMarked(void * const address, const int64_t bufferId, const int64_t configurationId, const uint32_t dataSizeInBytes) {
	const BufferRange accessBuffer = BufferRange((uint8_t*) address, ((uint8_t*) address) + 1); //zero-sized access would be ignore in the case of a pointer to the buffer's first element

	const AllocatedBuffersSet::const_iterator it = ApproxInter::allocatedBuffers.find(accessBuffer);

	if (it != ApproxInter::allocatedBuffers.cend()) {
		ApproxSS::add_approx(it->m_initialAddress, it->m_finalAddress, bufferId, configurationId, dataSizeInBytes);
	} else {
		std::cout << "ApproxInter WARNING: buffer not marked for add_approx." << std::endl;
	}
}

void ApproxInter::UninstrumentIfMarked(void * const address) {
	const BufferRange accessBuffer = BufferRange((uint8_t*) address, ((uint8_t*) address) + 1); //zero-sized access would be ignore in the case of a pointer to the buffer's first element

	const AllocatedBuffersSet::const_iterator it = ApproxInter::allocatedBuffers.find(accessBuffer);

	if (it != ApproxInter::allocatedBuffers.cend()) {
		ApproxSS::remove_approx(it->m_initialAddress, it->m_finalAddress);
	} else {
		std::cout << "ApproxInter WARNING: buffer not marked for remove_approx." << std::endl;
	}
}

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