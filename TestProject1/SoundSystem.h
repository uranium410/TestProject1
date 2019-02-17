#pragma once
#include "AllHead.h"
namespace BasicSystem {
	namespace SoundSystem {
		class SoundData {
		public:
			IXAudio2SourceVoice* source_voice;
			CWaveFile* wav;
			bool eof;
			bool loop=false;
			bool se = false;
			int loop_point=0;
			std::vector< BYTE > data[2];
			int primary = 0;
			int secondary = 1;
			DWORD write = 0;                            //èëÇ´çûÇ›ÉJÅ[É\Éã

		};


		void init();
		void cleanup();
		int LoadSound(LPTSTR _soundName, bool Loop = false,bool SE=false);
		void add_next_buffer(int sourceVoiceID);
		void polling(int sourveVoiceID);
		void flip(int sourceVoiceID);
		void SoundReset(int sourceVoiceID);
	}
}