#ifndef APPROXME_H
#define	APPROXME_H

#include <iostream>
#include <set>
#include "approx.h"

#define APPROX_RECO_BUFFER false
#define APPROX_ORIG_BUFFER false
#define APPROX_FILT_BUFFER_V1 false //GENERALIST
#define APPROX_FILT_BUFFER_V2 true  //SPECIFIC

class BufferRange {
	public:
		uint8_t * const m_initialAddress;
		uint8_t const * const m_finalAddress;

		BufferRange(uint8_t * const initialAddress, uint8_t const * const finalAddress);

		//overlapping ranges are considered equivalent
		friend bool operator<(const BufferRange& lhv, const BufferRange& rhv) {  
			return lhv.m_finalAddress <= rhv.m_initialAddress;
		}
};

typedef std::set<BufferRange> AllocatedBuffersSet;

class ApproxInter {
	private:
		static AllocatedBuffersSet allocatedBuffers;

    public:
		static void MarkBuffer(const BufferRange& toMark);
		static void UnmarkBuffer(const BufferRange& toUnmark);
		static void UnmarkBuffer(void const * const address);
		static void InstrumentIfMarked(void * const address, const int64_t bufferId, const int64_t configurationId, const uint32_t dataSizeInBytes);
		static void UninstrumentIfMarked(void * const address);
};

#endif