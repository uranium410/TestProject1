#pragma once


//-----------------------------------------------------------------------------
// File: DSUtil.h
//
// Desc: 
//
// Copyright (c) 1999-2000 Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
#ifndef DSUTIL_H
#define DSUTIL_H

#include <windows.h>
#include <mmsystem.h>
//#include <mmreg.h>
#include <dsound.h>



namespace mof{


	//-----------------------------------------------------------------------------
	// Typing macros 
	//-----------------------------------------------------------------------------
	#define WAVEFILE_READ   1
	#define WAVEFILE_WRITE  2

	#define DSUtil_StopSound(s)         { if(s) s->Stop(); }
	#define DSUtil_PlaySound(s)         { if(s) s->Play( 0, 0 ); }
	#define DSUtil_PlaySoundLooping(s)  { if(s) s->Play( 0, DSBPLAY_LOOPING ); }


	#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
	#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
	#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

	//-----------------------------------------------------------------------------
	// Name: class CWaveFile
	// Desc: Encapsulates reading or writing sound data to or from a wave file
	//-----------------------------------------------------------------------------
	class CWaveFile
	{
	public:
		WAVEFORMATEX* m_pwfx;        // Pointer to WAVEFORMATEX structure
		HMMIO         m_hmmio;       // MM I/O handle for the WAVE
		MMCKINFO      m_ck;          // Multimedia RIFF chunk
		MMCKINFO      m_ckRiff;      // Use in opening a WAVE file
		DWORD         m_dwSize;      // The size of the wave file
		MMIOINFO      m_mmioinfoOut;
    
		BOOL          m_bIsReadingFromMemory;
		BYTE*         m_pbData;
		BYTE*         m_pbDataCur;
		ULONG         m_ulDataSize;

		//WAVEFORMATEX* m_pwfx;
		//HMMIO m_hmmio;
		char* m_pResourceBuffer;
		//DWORD m_dwSize;
		//BOOL m_bIsReadingFromMemory;
		DWORD         m_dwFlags;

	protected:
		HRESULT readMMIO();
		HRESULT writeMMIO( WAVEFORMATEX *pwfxDest );

	public:
		CWaveFile();
		~CWaveFile();

		HRESULT open( LPTSTR strFileName, DWORD dwFlags );
		HRESULT openFromMemory( BYTE* pbData, ULONG ulDataSize, WAVEFORMATEX* pwfx, DWORD dwFlags );
		HRESULT close();

		HRESULT read( BYTE* pBuffer, DWORD dwSizeToRead, DWORD* pdwSizeRead );
		HRESULT write( UINT nSizeToWrite, BYTE* pbData, UINT* pnSizeWrote );

		DWORD   getSize();
		HRESULT resetFile();
		WAVEFORMATEX* getFormat() { return m_pwfx; };
		bool Seek(int offset, int origin)
		{
			// Seek to the data
			if (-1 == mmioSeek(m_hmmio, offset, origin))
				return false;

			m_ck.cksize -= offset;

			return true;
		}

		bool eof;
		bool loop;
		int loop_point;
	};

};


#endif // DSUTIL_H