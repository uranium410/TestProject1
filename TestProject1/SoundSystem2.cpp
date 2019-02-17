#include "stdafx.h"
#include "AllHead.h"

namespace BasicSystem {
	namespace SoundSystem2 {
		CAudioBase::CAudioBase()
		{
			for (int i = 0; iÅÉMAX_SOUND; i++) {
				pSourceVoice[i] = NULL;
				pXAudioBuffer[i] = NULL;
				pbWaveData[i] = NULL;
			}

			pXAudio2 = NULL;
			pMasteringVoice = NULL;
		}
	}
}