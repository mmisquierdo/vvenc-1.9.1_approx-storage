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

void ApproxInter::UninstrumentIfMarked(void * const address, const bool giveAwayRecords /*= true*/) {
	const BufferRange accessBuffer = BufferRange((uint8_t*) address, ((uint8_t*) address) + 1); //zero-sized access would be ignore in the case of a pointer to the buffer's first element

	const AllocatedBuffersSet::const_iterator it = ApproxInter::allocatedBuffers.find(accessBuffer);

	if (it != ApproxInter::allocatedBuffers.cend()) {
		ApproxSS::remove_approx(it->m_initialAddress, it->m_finalAddress, giveAwayRecords);
	} else {
		std::cout << "ApproxInter WARNING: buffer not marked for remove_approx." << std::endl;
	}
}

void ApproxInter::PrintMacroState(const std::string& macroName, const bool macroStatus, const std::string& tab /*= "\t"*/) {
	std::cout << tab << macroName << ": " << (macroStatus ? "Enabled" : "Disabled") << std::endl;
}

void ApproxInter::PrintMacrosStates() {
	std::cout << "APPROX MACROS STATES" << std::endl;

	ApproxInter::PrintMacroState("MATHEUS_INSTRUMENTATION", 			MATHEUS_INSTRUMENTATION);
	ApproxInter::PrintMacroState("FELIPE_INSTRUMENTATION", 				FELIPE_INSTRUMENTATION);

	ApproxInter::PrintMacroState("APPROX_RECO_BUFFER_INTER", 			APPROX_RECO_BUFFER_INTER);
	ApproxInter::PrintMacroState("APPROX_RECO_BUFFER_INTER_PATTERN", 	APPROX_RECO_BUFFER_INTER_PATTERN);
	ApproxInter::PrintMacroState("APPROX_RECO_BUFFER_INTER_TZ", 		APPROX_RECO_BUFFER_INTER_TZ);
	ApproxInter::PrintMacroState("APPROX_RECO_BUFFER_INTER_FAST", 		APPROX_RECO_BUFFER_INTER_FAST);
	ApproxInter::PrintMacroState("APPROX_RECO_BUFFER_INTER_FRACTIONAL",	APPROX_RECO_BUFFER_INTER_FRACTIONAL);
	ApproxInter::PrintMacroState("APPROX_RECO_BUFFER_INTER_AFFINE", 	APPROX_RECO_BUFFER_INTER_AFFINE);

	ApproxInter::PrintMacroState("APPROX_ORIG_BUFFER", 					APPROX_ORIG_BUFFER);
	ApproxInter::PrintMacroState("APPROX_FILT_BUFFER_V1", 				APPROX_FILT_BUFFER_V1);
	ApproxInter::PrintMacroState("APPROX_FILT_BUFFER_V2", 				APPROX_FILT_BUFFER_V2);
	ApproxInter::PrintMacroState("APPROX_PRED_BUFFER", 					APPROX_PRED_BUFFER);

	std::cout << std::endl;
}



#if FELIPE_INSTRUMENTATION
	#if APPROX_RECO_BUFFER_INTER
		//double ApproxInter::MEReadBER;
		//double ApproxInter::MEWriteBER;

		unsigned ApproxInter::RECO::frameBufferWidth, ApproxInter::RECO::frameBufferHeight;
		unsigned ApproxInter::RECO::xMargin, ApproxInter::RECO::yMargin;

		bool ApproxInter::RECO::collectBufferSize, ApproxInter::RECO::tmpBool;

		int ApproxInter::RECO::debugEnable;

		std::fstream ApproxInter::RECO::fp;

		void ApproxInter::RECO::init() {
			//MEReadBER = 0.0;
			//MEWriteBER = 0.0;
			collectBufferSize = true;
			tmpBool = false;
		}

		void ApproxInter::RECO::initDebug() {
			if(debugEnable) {
				fp.open("debug.txt", std::fstream::out);
			}
		}
	#endif

	#if APPROX_ORIG_BUFFER
		//double ApproxInter::MEReadBER;
		//double ApproxInter::MEWriteBER;

		unsigned ApproxInter::ORIG::frameOrigBufferWidth, ApproxInter::ORIG::frameOrigBufferHeight;
		//unsigned ApproxInter::xMargin, ApproxInter::yMargin;

		bool ApproxInter::ORIG::collectBufferSize, ApproxInter::ORIG::tmpBool;

		int ApproxInter::ORIG::debugEnable;

		std::fstream ApproxInter::ORIG::fp;

		void ApproxInter::ORIG::init() {
			collectBufferSize = true;
			tmpBool = false;
		}

		void ApproxInter::ORIG::initDebug() {
			if(debugEnable) {
				fp.open("debug.txt", std::fstream::out);
			}
		}
	#endif

	#if APPROX_FILT_BUFFER_V1 || APPROX_FILT_BUFFER_V2	
		//<Felipe>
			int ApproxInter::FILT::extWidthFiltered, ApproxInter::FILT::extHeightFiltered;
		//</Felipe>
	#endif
#endif