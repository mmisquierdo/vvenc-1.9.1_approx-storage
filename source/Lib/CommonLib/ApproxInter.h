#ifndef APPROXME_H
#define	APPROXME_H

	#include <iostream>
	#include <fstream>
	#include <set>
	#include <mutex>
	#include "approx.h"
	#include "CommonDef.h"

	#define MATHEUS_INSTRUMENTATION 			false
	#define FELIPE_INSTRUMENTATION (!MATHEUS_INSTRUMENTATION && false)

	#define MATHEUS_SKIP_FRACTIONAL_MOTION_ESTIMATION false
	#define MATHEUS_xPatternSearchIntRefine_ITERATED_POS 9 /*up to 9: default*/

	#define APPROX_RECO_BUFFER_INTER 					false 	//ativa instrumentação em toda a ME (excluindo affine)
	#define APPROX_ORIG_BUFFER_INTER 					false 	//ativa instrumentação em toda a ME (excluindo affine), para ORIG e TEMP_ORIG

	//#define APPROX_RECO_BUFFER_INTER_MVP 		true 
	//#define APPROX_RECO_BUFFER_INTER_PATTERN 	true
	#define APPROX_RECO_BUFFER_INTER_MVP_AND_PATTERN 	false
	#define APPROX_RECO_BUFFER_INTER_TZ 				false
	#define APPROX_RECO_BUFFER_INTER_FAST 				false
	#define APPROX_RECO_BUFFER_INTER_REFINEMENT 		false
	#define APPROX_RECO_BUFFER_INTER_FRACTIONAL_WHOLE	false

	#define APPROX_ORIG_BUFFER_INTER_IME 				false
	#define APPROX_ORIG_BUFFER_INTER_REFINEMENT			false
	#define APPROX_ORIG_BUFFER_INTER_FRACTIONAL_WHOLE	false

	#define APPROX_RECO_BUFFER_INTER_AFFINE 			false
	#define APPROX_ORIG_BUFFER_INTER_AFFINE 			false	//TODO!!!: check for temporary copies

	#define APPROX_FILT_BUFFER_V1 						false	//GENERALIST
	#define APPROX_FILT_BUFFER_V2 						false	//SPECIFIC
	#define APPROX_PRED_BUFFER 							false


	#define APPROX_FME_BEST_MV_COST_RECALC 				false
	#define APPROX_FME_RECO 							false
	#define APPROX_FME_ORIG 							false
	#define APPROX_FME_FILT								false
	/*#define APPROX_FME_HP_RECO							true
	#define APPROX_FME_HP_ORIG							true
	#define APPROX_FME_QP_RECO							true
	#define APPROX_FME_QP_ORIG							true*/

	#define PRINT_COST 									false

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

			//FME_BEST_MV_COST_RECALC
			extern uint32_t fme_uiDirecBest;



		//public:
			namespace BufferId {
				constexpr int64_t OTHERS = 0;



				/*constexpr int64_t RECO_MOTION_ESTIMATION 					= 0;
				constexpr int64_t RECO_AFFINE_MOTION_ESTIMATION 			= 1;
				constexpr int64_t ORIG_MOTION_ESTIMATION 					= 2;
				constexpr int64_t TEMP_ORIG_MOTION_ESTIMATION 				= 11;
				constexpr int64_t ORIG_AFFINE_MOTION_ESTIMATION 			= 3;
				constexpr int64_t TEMP_ORIG_AFFINE_MOTION_ESTIMATION		= 13;
				//constexpr int64_t FILT_MOTION_ESTIMATION_TEMP 			= 4;
				//constexpr int64_t FILT_MOTION_ESTIMATION 					= 5;
				constexpr int64_t PRED_AFFINE_MOTION_ESTIMATION 			= 6;

				//constexpr int64_t RECO_MOTION_ESTIMATION_MVP 				= 12;
				//constexpr int64_t RECO_MOTION_ESTIMATION_PATTERN 			= 7;
				constexpr int64_t RECO_MOTION_ESTIMATION_MVP_AND_PATTERN	= 7;
				constexpr int64_t RECO_MOTION_ESTIMATION_TZ 				= 8;
				constexpr int64_t RECO_MOTION_ESTIMATION_FAST 				= 9;
				constexpr int64_t RECO_MOTION_ESTIMATION_FRACTIONAL 		= 10;
				constexpr int64_t RECO_MOTION_ESTIMATION_REFINEMENT 		= 14;

				constexpr int64_t ORIG_MOTION_ESTIMATION_IME 				= 15;
				constexpr int64_t ORIG_MOTION_ESTIMATION_FRACTIONAL 		= 16;
				constexpr int64_t ORIG_MOTION_ESTIMATION_REFINEMENT 		= 17;

				constexpr int64_t FME_RECO 									= RECO_MOTION_ESTIMATION_FRACTIONAL;
				constexpr int64_t FME_ORIG 									= ORIG_MOTION_ESTIMATION_FRACTIONAL;

				/*constexpr int64_t FME_RECO_HR								= 20;
				constexpr int64_t FME_RECO_QR								= 21;
				constexpr int64_t FME_ORIG_HR								= 22;
				constexpr int64_t FME_ORIG_QR								= 23;*/

				/*static constexpr auto FME_FILT_OFFSET						= "1";
				static constexpr auto FME_FILT_TEMP_OFFSET					= "20";


				extern int64_t FME_FILT			[vvenc::LUMA_INTERPOLATION_FILTER_SUB_SAMPLE_POSITIONS_SIGNAL][vvenc::LUMA_INTERPOLATION_FILTER_SUB_SAMPLE_POSITIONS_SIGNAL][vvenc::ComponentID::MAX_NUM_COMP];
				extern int64_t FME_FILT_TEMP	[vvenc::LUMA_INTERPOLATION_FILTER_SUB_SAMPLE_POSITIONS_SIGNAL][vvenc::ComponentID::MAX_NUM_COMP];*/
			}

			namespace ConfigurationId {
				static constexpr int64_t JUST_TRACKING						= 0;
				static constexpr int64_t PRECISE_KNOB						= 2;
				static constexpr int64_t APPROXIMATE_KNOB					= 1;

				constexpr int64_t OTHER = JUST_TRACKING




				/*constexpr int64_t RECO_MOTION_ESTIMATION 					= JUST_TRACKING;
				constexpr int64_t RECO_AFFINE_MOTION_ESTIMATION 			= JUST_TRACKING;
				constexpr int64_t ORIG_MOTION_ESTIMATION 					= JUST_TRACKING;
				constexpr int64_t TEMP_ORIG_MOTION_ESTIMATION 				= JUST_TRACKING;
				constexpr int64_t ORIG_AFFINE_MOTION_ESTIMATION 			= JUST_TRACKING;
				constexpr int64_t TEMP_ORIG_AFFINE_MOTION_ESTIMATION		= JUST_TRACKING;
				constexpr int64_t FILT_MOTION_ESTIMATION_TEMP 				= JUST_TRACKING;
				constexpr int64_t FILT_MOTION_ESTIMATION 					= JUST_TRACKING;
				constexpr int64_t PRED_AFFINE_MOTION_ESTIMATION 			= JUST_TRACKING;

				//constexpr int64_t RECO_MOTION_ESTIMATION_MVP 				= 0;
				//constexpr int64_t RECO_MOTION_ESTIMATION_PATTERN 			= 0;
				constexpr int64_t RECO_MOTION_ESTIMATION_MVP_AND_PATTERN	= JUST_TRACKING;
				constexpr int64_t RECO_MOTION_ESTIMATION_TZ 				= JUST_TRACKING;
				constexpr int64_t RECO_MOTION_ESTIMATION_FAST 				= JUST_TRACKING;
				constexpr int64_t RECO_MOTION_ESTIMATION_FRACTIONAL 		= JUST_TRACKING;
				constexpr int64_t RECO_MOTION_ESTIMATION_REFINEMENT 		= JUST_TRACKING;

				constexpr int64_t ORIG_MOTION_ESTIMATION_IME 				= JUST_TRACKING;
				constexpr int64_t ORIG_MOTION_ESTIMATION_FRACTIONAL 		= JUST_TRACKING;
				constexpr int64_t ORIG_MOTION_ESTIMATION_REFINEMENT 		= JUST_TRACKING;

				constexpr int64_t FME_RECO 									= RECO_MOTION_ESTIMATION_FRACTIONAL;
				constexpr int64_t FME_ORIG 									= ORIG_MOTION_ESTIMATION_FRACTIONAL;

				/*constexpr int64_t FME_RECO_HR								= JUST_TRACKING;
				constexpr int64_t FME_RECO_QR								= JUST_TRACKING;
				constexpr int64_t FME_ORIG_HR								= JUST_TRACKING;
				constexpr int64_t FME_ORIG_QR								= JUST_TRACKING;*/

				/*constexpr int64_t FME_FILT									= JUST_TRACKING;	
				constexpr int64_t FME_FILT_TEMP								= JUST_TRACKING;*/
			}


			#if PRINT_COST
				extern double bestTempCost;
			#endif


			void MarkBuffer(const BufferRange& toMark);
			void UnmarkBuffer(const BufferRange& toUnmark);
			void UnmarkBuffer(void const * const address);
			void InstrumentIfMarked(void * const address, const int64_t bufferId, const int64_t configurationId, const uint32_t dataSizeInBytes);
			void ReinstrumentIfMarked(void * const address, const int64_t bufferId, const int64_t configurationId, const uint32_t dataSizeInBytes);
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

			#if APPROX_ORIG_BUFFER_INTER
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