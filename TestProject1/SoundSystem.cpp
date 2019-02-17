/*
↓以下から流用しました↓
http://d.hatena.ne.jp/setuna-kanata/20091220/1261317927
*/
#include "stdafx.h"
#include "AllHead.h"

//プライマリとセカンダリの２つのバッファを用意する。
//プライマリは現在再生中のバッファ
//セカンダリは新しいデータの書き込み可能なバッファ
//プライマリの再生が終わったらプライマリとセカンダリを入れ替えて、
//常にプライマリが再生状態になるようにする

namespace BasicSystem {


	namespace SoundSystem {
		
		IXAudio2* xaudio;
		IXAudio2MasteringVoice* mastering_voice;
		std::vector<SoundData> source_voice;

		
		/*初期化処理*/
		
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

		/*XAudioのクリーンアップ*/
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
			//  WAVファイルを開く
			//
			hr = temp.wav->Open(_soundName,NULL,WAVEFILE_READ);
			

			//
			//  WAVファイルのWAVEFORMATEXを使ってSourceVoiceを作成
			//

			WAVEFORMATEX* format = temp.wav->GetFormat();
			hr = xaudio->CreateSourceVoice(&temp.source_voice, format);

			source_voice.push_back(temp);
			int pos = source_voice.size() - 1;


			source_voice[pos].se = SE;


			//
			//  1秒のバッファを２つ用意
			//
			for (int i = 0; i < 2; i++)
				source_voice[pos].data[i].resize(format->nAvgBytesPerSec * 0.5);

			//
			//  あらかじめバッファを追加しておく
			//
			add_next_buffer(pos);

			//
			//  再生
			//
			source_voice[pos].source_voice->Start();

			/*
			//メッセージループ、またはゲームループ
			while (bool b = true)
			{
				//とりあえず、ESCキーで終了
				if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)break;

				//再生状態を常に監視する
				polling(pos);

				Sleep(10);
			}*/
			return pos;
		}


		//セカンダリに新しいデータを書き込んで、再生キューに追加する
		void add_next_buffer(int sourceVoiceID)
		{
			std::vector< BYTE >& data_ = source_voice[sourceVoiceID].data[source_voice[sourceVoiceID].secondary];
			//
			//  secndaryにデータを書き込んで、書き込みカーソルを進める
			//
			DWORD read;     //実際にReadしたバイト数
			if (FAILED(source_voice[sourceVoiceID].wav->Read(&data_[0], data_.size(), &read)))
				throw "Read";
			source_voice[sourceVoiceID].write += read;

			//
			//  SourceVoiceにデータを送信
			//
			XAUDIO2_BUFFER buffer = { 0 };
			buffer.AudioBytes = read;                       //バッファのバイト数
			buffer.pAudioData = &data_[0];                //バッファの先頭アドレス
			if (source_voice[sourceVoiceID].wav->GetSize() <= source_voice[sourceVoiceID].write)
				buffer.Flags = XAUDIO2_END_OF_STREAM;
			source_voice[sourceVoiceID].source_voice->SubmitSourceBuffer(&buffer);

			//
			//primaryとsecondaryの入れ替え
			//
			flip(sourceVoiceID);
		}


		//プライマリとセカンダリのフリップ
		void flip(int sourceVoiceID)
		{
			std::swap(source_voice[sourceVoiceID].primary, source_voice[sourceVoiceID].secondary);
		}

		void polling(int sourceVoiceID)
		{
			//状態の取得
			XAUDIO2_VOICE_STATE state;
			source_voice[sourceVoiceID].source_voice->GetState(&state);

			//再生キューに常に２つのバッファを溜めておく
			if (!source_voice[sourceVoiceID].eof && state.BuffersQueued < 2)
			{
				//書き込みカーソルがWAVファイルのサイズを超えている場合、
				//  ループ再生を行う場合、ファイルをループ位置までシーク
				//  ループ再生しない場合、再生終了
				if (source_voice[sourceVoiceID].write >= source_voice[sourceVoiceID].wav->GetSize())
				{
					if (source_voice[sourceVoiceID].loop)
					{
						//dataチャンクの先頭に戻す
						source_voice[sourceVoiceID].wav->ResetFile();
						//dataチャンクの先頭からloop_pointまでシーク
						source_voice[sourceVoiceID].wav->Seek(source_voice[sourceVoiceID].loop_point, SEEK_CUR);
						//書き込みカーソルをloop_pointまで移動
						source_voice[sourceVoiceID].write = source_voice[sourceVoiceID].loop_point;
					}
					else {
						source_voice[sourceVoiceID].eof = true;
					}
				}

				if (!source_voice[sourceVoiceID].eof)
				{
					//バッファにデータを書き込んで、再生キューに追加
					add_next_buffer(sourceVoiceID);
				}
			}

		}
		void SoundReset(int sourceVoiceID) {
			source_voice[sourceVoiceID].source_voice->Stop();

			//dataチャンクの先頭に戻す
			source_voice[sourceVoiceID].wav->ResetFile();
			//dataチャンクの先頭からloop_pointまでシーク
			source_voice[sourceVoiceID].wav->Seek(source_voice[sourceVoiceID].loop_point, SEEK_CUR);
			//書き込みカーソルをloop_pointまで移動
			source_voice[sourceVoiceID].write = source_voice[sourceVoiceID].loop_point;
			source_voice[sourceVoiceID].eof = false;
			
			add_next_buffer(sourceVoiceID);
			source_voice[sourceVoiceID].source_voice->Start();
		}


	}

}