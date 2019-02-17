/*
���ȉ����痬�p���܂�����
http://d.hatena.ne.jp/setuna-kanata/20091220/1261317927
*/
#include "stdafx.h"
#include "AllHead.h"

//�v���C�}���ƃZ�J���_���̂Q�̃o�b�t�@��p�ӂ���B
//�v���C�}���͌��ݍĐ����̃o�b�t�@
//�Z�J���_���͐V�����f�[�^�̏������݉\�ȃo�b�t�@
//�v���C�}���̍Đ����I�������v���C�}���ƃZ�J���_�������ւ��āA
//��Ƀv���C�}�����Đ���ԂɂȂ�悤�ɂ���

namespace BasicSystem {


	namespace SoundSystem {
		
		IXAudio2* xaudio;
		IXAudio2MasteringVoice* mastering_voice;
		std::vector<SoundData> source_voice;

		
		/*����������*/
		
		void init()
		{
			
			//
			//  Initialize XAudio2
			//
			HRESULT hr;
			hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

			//UINT32 flags = UINT32(0);

			hr = XAudio2Create(&xaudio, 0);

			//
			//  Create a mastering voice
			//
			hr = xaudio->CreateMasteringVoice(&mastering_voice);
		}

		/*XAudio�̃N���[���A�b�v*/
		void cleanup()
		{
			//
			// Cleanup XAudio2
			//
			int i;
			for (i = 0; i < source_voice.size(); i++) {
				source_voice[i].source_voice->Stop();
				source_voice[i].source_voice->DestroyVoice();
			}
			source_voice.clear();

			if (mastering_voice != 0)
			{
				mastering_voice->DestroyVoice();
				mastering_voice = 0;
			}
			if (xaudio != 0)
			{
				xaudio->Release();
				xaudio = 0;
			}
			CoUninitialize();
		}


		int LoadSound(LPTSTR _soundName, bool Loop, bool SE) {
			SoundData temp;
			temp.wav = new CWaveFile;

			HRESULT hr;

			//
			//  WAV�t�@�C�����J��
			//
			hr = temp.wav->Open(_soundName,NULL,WAVEFILE_READ);
			

			//
			//  WAV�t�@�C����WAVEFORMATEX���g����SourceVoice���쐬
			//

			WAVEFORMATEX* format = temp.wav->GetFormat();
			hr = xaudio->CreateSourceVoice(&temp.source_voice, format);

			source_voice.push_back(temp);
			int pos = source_voice.size() - 1;


			source_voice[pos].se = SE;


			//
			//  1�b�̃o�b�t�@���Q�p��
			//
			for (int i = 0; i < 2; i++)
				source_voice[pos].data[i].resize(format->nAvgBytesPerSec * 0.5);

			//
			//  ���炩���߃o�b�t�@��ǉ����Ă���
			//
			add_next_buffer(pos);

			//
			//  �Đ�
			//
			source_voice[pos].source_voice->Start();

			/*
			//���b�Z�[�W���[�v�A�܂��̓Q�[�����[�v
			while (bool b = true)
			{
				//�Ƃ肠�����AESC�L�[�ŏI��
				if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)break;

				//�Đ���Ԃ���ɊĎ�����
				polling(pos);

				Sleep(10);
			}*/
			return pos;
		}


		//�Z�J���_���ɐV�����f�[�^����������ŁA�Đ��L���[�ɒǉ�����
		void add_next_buffer(int sourceVoiceID)
		{
			std::vector< BYTE >& data_ = source_voice[sourceVoiceID].data[source_voice[sourceVoiceID].secondary];
			//
			//  secndary�Ƀf�[�^����������ŁA�������݃J�[�\����i�߂�
			//
			DWORD read;     //���ۂ�Read�����o�C�g��
			if (FAILED(source_voice[sourceVoiceID].wav->Read(&data_[0], data_.size(), &read)))
				throw "Read";
			source_voice[sourceVoiceID].write += read;

			//
			//  SourceVoice�Ƀf�[�^�𑗐M
			//
			XAUDIO2_BUFFER buffer = { 0 };
			buffer.AudioBytes = read;                       //�o�b�t�@�̃o�C�g��
			buffer.pAudioData = &data_[0];                //�o�b�t�@�̐擪�A�h���X
			if (source_voice[sourceVoiceID].wav->GetSize() <= source_voice[sourceVoiceID].write)
				buffer.Flags = XAUDIO2_END_OF_STREAM;
			source_voice[sourceVoiceID].source_voice->SubmitSourceBuffer(&buffer);

			//
			//primary��secondary�̓���ւ�
			//
			flip(sourceVoiceID);
		}


		//�v���C�}���ƃZ�J���_���̃t���b�v
		void flip(int sourceVoiceID)
		{
			std::swap(source_voice[sourceVoiceID].primary, source_voice[sourceVoiceID].secondary);
		}

		void polling(int sourceVoiceID)
		{
			//��Ԃ̎擾
			XAUDIO2_VOICE_STATE state;
			source_voice[sourceVoiceID].source_voice->GetState(&state);

			//�Đ��L���[�ɏ�ɂQ�̃o�b�t�@�𗭂߂Ă���
			if (!source_voice[sourceVoiceID].eof && state.BuffersQueued < 2)
			{
				//�������݃J�[�\����WAV�t�@�C���̃T�C�Y�𒴂��Ă���ꍇ�A
				//  ���[�v�Đ����s���ꍇ�A�t�@�C�������[�v�ʒu�܂ŃV�[�N
				//  ���[�v�Đ����Ȃ��ꍇ�A�Đ��I��
				if (source_voice[sourceVoiceID].write >= source_voice[sourceVoiceID].wav->GetSize())
				{
					if (source_voice[sourceVoiceID].loop)
					{
						//data�`�����N�̐擪�ɖ߂�
						source_voice[sourceVoiceID].wav->ResetFile();
						//data�`�����N�̐擪����loop_point�܂ŃV�[�N
						source_voice[sourceVoiceID].wav->Seek(source_voice[sourceVoiceID].loop_point, SEEK_CUR);
						//�������݃J�[�\����loop_point�܂ňړ�
						source_voice[sourceVoiceID].write = source_voice[sourceVoiceID].loop_point;
					}
					else {
						source_voice[sourceVoiceID].eof = true;
					}
				}

				if (!source_voice[sourceVoiceID].eof)
				{
					//�o�b�t�@�Ƀf�[�^����������ŁA�Đ��L���[�ɒǉ�
					add_next_buffer(sourceVoiceID);
				}
			}

		}
		void SoundReset(int sourceVoiceID) {
			source_voice[sourceVoiceID].source_voice->Stop();

			//data�`�����N�̐擪�ɖ߂�
			source_voice[sourceVoiceID].wav->ResetFile();
			//data�`�����N�̐擪����loop_point�܂ŃV�[�N
			source_voice[sourceVoiceID].wav->Seek(source_voice[sourceVoiceID].loop_point, SEEK_CUR);
			//�������݃J�[�\����loop_point�܂ňړ�
			source_voice[sourceVoiceID].write = source_voice[sourceVoiceID].loop_point;
			source_voice[sourceVoiceID].eof = false;
			
			add_next_buffer(sourceVoiceID);
			source_voice[sourceVoiceID].source_voice->Start();
		}


	}

}