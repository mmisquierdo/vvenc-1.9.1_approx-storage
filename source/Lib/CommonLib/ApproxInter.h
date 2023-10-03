#ifndef APPROXME_H
#define	APRROXME_H

#include <fstream>
#include <set>

class BufferRange {
	public:
		uint8_t* const m_initialAddress;
		uint8_t const * const m_finalAddress;

		BufferRange(uint8_t * const initialAddress, uint8_t const * const finalAddress);

		//overlapping ranges are considered equivalent
		friend bool operator<(const BufferRange& lhv, const BufferRange& rhv) {  
			return lhv.m_finalAddress <= rhv.m_initialAddress;
		}
};

typedef std::set<BufferRange> AllocatedPelBuffersSet;

class ApproxInter {

    public:
		static AllocatedPelBuffersSet allocatedPelBuffers;

        /*static std::fstream fp;
        static int debugEnable;

        //static double MEReadBER, MEWriteBER;
        static unsigned frameBufferWidth, frameBufferHeight;
        static unsigned xMargin, yMargin;
        static bool collectBufferSize, tmpBool;

        static void init();
        static void initDebug();*/
};

#endif