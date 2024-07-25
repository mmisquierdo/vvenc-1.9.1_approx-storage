#ifndef APPROXME_H
#define	APPROXME_H

	#include <iostream>
	#include <fstream>
	#include <set>
	#include <mutex>
	#include "approx.h"

	#define MATHEUS_INSTRUMENTATION 			true
	#define FELIPE_INSTRUMENTATION (!MATHEUS_INSTRUMENTATION && false)

	#define MATHEUS_SKIP_FRACTIONAL_MOTION_ESTIMATION false
	#define MATHEUS_xPatternSearchIntRefine_ITERATED_POS 9 /*up to 9: default*/

	#define APPROX_RECO_BUFFER_INTER 			false //ativa instrumentação em toda a ME (excluindo affine)

	#define APPROX_RECO_BUFFER_INTER_MVP 		true 
	#define APPROX_RECO_BUFFER_INTER_PATTERN 	true 
	#define APPROX_RECO_BUFFER_INTER_TZ 		true
	#define APPROX_RECO_BUFFER_INTER_FAST 		true
	#define APPROX_RECO_BUFFER_INTER_REFINEMENT false
	#define APPROX_RECO_BUFFER_INTER_FRACTIONAL	false
	#define APPROX_RECO_BUFFER_INTER_AFFINE 	false


	#define APPROX_ORIG_BUFFER 					false
	#define APPROX_FILT_BUFFER_V1 				false	//GENERALIST
	#define APPROX_FILT_BUFFER_V2 				false	//SPECIFIC
	#define APPROX_PRED_BUFFER 					false

	#define PRINT_COST 							false

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
			extern AllocatedBuffersSet allocatedBuffers; //use methods to manipulate
			extern std::mutex allocatedBuffersMutex;

		//public:
			namespace BufferId {
				constexpr int64_t RECO_MOTION_ESTIMATION 				= 0;
				constexpr int64_t RECO_AFFINE_MOTION_ESTIMATION 		= 1;
				constexpr int64_t ORIG_MOTION_ESTIMATION 				= 2;
				constexpr int64_t TEMP_ORIG_MOTION_ESTIMATION 			= 11;
				constexpr int64_t ORIG_AFFINE_MOTION_ESTIMATION 		= 3;
				constexpr int64_t TEMP_ORIG_AFFINE_MOTION_ESTIMATION	= 13;
				constexpr int64_t FILT_MOTION_ESTIMATION_TEMP 			= 4;
				constexpr int64_t FILT_MOTION_ESTIMATION 				= 5;
				constexpr int64_t PRED_AFFINE_MOTION_ESTIMATION 		= 6;

				constexpr int64_t RECO_MOTION_ESTIMATION_MVP 			= 12;
				constexpr int64_t RECO_MOTION_ESTIMATION_PATTERN 		= 7;
				constexpr int64_t RECO_MOTION_ESTIMATION_TZ 			= 8;
				constexpr int64_t RECO_MOTION_ESTIMATION_FAST 			= 9;
				constexpr int64_t RECO_MOTION_ESTIMATION_FRACTIONAL 	= 10;
				constexpr int64_t RECO_MOTION_ESTIMATION_REFINEMENT 	= 14;
			}

			namespace ConfigurationId {
				constexpr int64_t RECO_MOTION_ESTIMATION 				= 0;
				constexpr int64_t RECO_AFFINE_MOTION_ESTIMATION 		= 0;
				constexpr int64_t ORIG_MOTION_ESTIMATION 				= 0;
				constexpr int64_t TEMP_ORIG_MOTION_ESTIMATION 			= 0;
				constexpr int64_t ORIG_AFFINE_MOTION_ESTIMATION 		= 0;
				constexpr int64_t TEMP_ORIG_AFFINE_MOTION_ESTIMATION	= 0;
				constexpr int64_t FILT_MOTION_ESTIMATION_TEMP 			= 0;
				constexpr int64_t FILT_MOTION_ESTIMATION 				= 0;
				constexpr int64_t PRED_AFFINE_MOTION_ESTIMATION 		= 0;

				constexpr int64_t RECO_MOTION_ESTIMATION_MVP 			= 1;
				constexpr int64_t RECO_MOTION_ESTIMATION_PATTERN 		= 1;
				constexpr int64_t RECO_MOTION_ESTIMATION_TZ 			= 1;
				constexpr int64_t RECO_MOTION_ESTIMATION_FAST 			= 1;
				constexpr int64_t RECO_MOTION_ESTIMATION_FRACTIONAL 	= 0;
				constexpr int64_t RECO_MOTION_ESTIMATION_REFINEMENT 	= 0;
			}


			#if PRINT_COST
				extern double bestTempCost;
			#endif


			void MarkBuffer(const BufferRange& toMark);
			void UnmarkBuffer(const BufferRange& toUnmark);
			void UnmarkBuffer(void const * const address);
			void InstrumentIfMarked(void * const address, const int64_t bufferId, const int64_t configurationId, const uint32_t dataSizeInBytes);
			void UninstrumentIfMarked(void * const address, const bool giveAwayRecords = true);

			void PrintMacrosStates();
			void PrintMacroState(const std::string& macroName, const bool macroStatus, const std::string& tab = "\t");

			void PrintBuffersInfo();
			void PrintBufferInfo(const std::string& bufferName, const int64_t bufferId, const int64_t configurationId, const std::string& tab = "\t");

		#if FELIPE_INSTRUMENTATION
			#if APPROX_RECO_BUFFER_INTER
				namespace RECO { 
					//public:
					extern std::fstream fp;
					extern int debugEnable;

					//double MEReadBER, MEWriteBER;
					extern unsigned frameBufferWidth, frameBufferHeight;
					extern unsigned xMargin, yMargin;
					extern bool collectBufferSize, tmpBool;

					void init();
					void initDebug();
				}
			#endif

			#if APPROX_ORIG_BUFFER
				namespace ORIG {
					//public:
					extern std::fstream fp;
					extern int debugEnable;

					//double MEReadBER, MEWriteBER;
					extern unsigned frameOrigBufferWidth, frameOrigBufferHeight;
					////unsigned xMargin, yMargin;
					extern bool collectBufferSize, tmpBool;

					void init();
					void initDebug();
				}
			#endif

			#if APPROX_FILT_BUFFER_V1 || APPROX_FILT_BUFFER_V2
				namespace FILT {
					//<Felipe>
					extern int extWidthFiltered, extHeightFiltered;
					//</Felipe>
				}
			#endif
		#endif
	}

#endif