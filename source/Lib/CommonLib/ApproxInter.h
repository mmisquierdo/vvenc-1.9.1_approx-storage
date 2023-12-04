#ifndef APPROXME_H
#define	APPROXME_H

#include <iostream>
#include <fstream>
#include <set>
#include "approx.h"


#define MATHEUS_INSTRUMENTATION false
#define FELIPE_INSTRUMENTATION (!MATHEUS_INSTRUMENTATION && true)


#define APPROX_RECO_BUFFER true
#define APPROX_ORIG_BUFFER true
#define APPROX_FILT_BUFFER_V1 false	//GENERALIST
#define APPROX_FILT_BUFFER_V2 false	//SPECIFIC

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

namespace ApproxInter {
	//private:
		static AllocatedBuffersSet allocatedBuffers; //use methods to manipulate

    //public:
		constexpr int64_t RECO_MOTION_ESTIMATION_BID = 0;
		constexpr int64_t RECO_AFFINE_MOTION_ESTIMATION_BID = 1;
		constexpr int64_t ORIG_MOTION_ESTIMATION_BID = 2; 


		static void MarkBuffer(const BufferRange& toMark);
		static void UnmarkBuffer(const BufferRange& toUnmark);
		static void UnmarkBuffer(void const * const address);
		static void InstrumentIfMarked(void * const address, const int64_t bufferId, const int64_t configurationId, const uint32_t dataSizeInBytes);
		static void UninstrumentIfMarked(void * const address, const bool giveAwayRecords = true);

	#if FELIPE_INSTRUMENTATION
		#if APPROX_RECO_BUFFER
			namespace RECO { 
				//public:
				static std::fstream fp;
				static int debugEnable;

				//static double MEReadBER, MEWriteBER;
				static unsigned frameBufferWidth, frameBufferHeight;
				static unsigned xMargin, yMargin;
				static bool collectBufferSize, tmpBool;

				static void init();
				static void initDebug();
			}
		#endif

		#if APPROX_ORIG_BUFFER
			namespace ORIG {
				//public:
				static std::fstream fp;
				static int debugEnable;

				//static double MEReadBER, MEWriteBER;
				static unsigned frameOrigBufferWidth, frameOrigBufferHeight;
				////static unsigned xMargin, yMargin;
				static bool collectBufferSize, tmpBool;

				static void init();
				static void initDebug();
			}
		#endif
	#endif
}

#endif