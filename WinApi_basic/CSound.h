#pragma once
#include "CRes.h"

#include "CSoundMgr.h"

class CSound :
    public CRes
{
private:
    LPDIRECTSOUNDBUFFER         m_pSoundBuffer; // 소리를 저장하는 공간
    DSBUFFERDESC                          m_tBuffInfo;        // 
    int                                                 m_iVolume;

public:
    int Load(const wchar_t* _strPath);

    // 일반 재생
    void Play(bool _bLoop = false);

    // BGM 으로 재생
    void PlayToBGM(bool _bLoop = false);
    
    void Stop(bool _bReset = false);

    // 볼륨 범위 ( 0 ~ 100 )
    void SetVolume(float _fVolume);

    void SetPosition(float _fPosition); // 0 ~ 100 사이 

private:
    bool LoadWaveSound(const wstring& _strPath);
    int GetDecibel(float  _fVolume);

public:
    CSound();
    virtual ~CSound();
};

