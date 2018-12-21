#include "stdafx.h"
#include "SoundManager.h"

JEONG_USING
SINGLETON_VAR_INIT(JEONG::SoundManager)

shared_ptr<SoundEffect> JEONG::SoundManager::m_NULLPTR1;
shared_ptr<SoundEffectInstance> JEONG::SoundManager::m_NULLPTR2;

JEONG::SoundManager::SoundManager()
{
}

JEONG::SoundManager::~SoundManager()
{
}

bool JEONG::SoundManager::Init()
{
	AUDIO_ENGINE_FLAGS Flag = AudioEngine_Default;
#ifdef _DEBUG
	Flag = Flag | AudioEngine_Debug;
#endif
	m_AudioEngine = make_unique<AudioEngine>(Flag);

	CreateSoundEffect("LogoBGM", TEXT("Over the top (short intro).wav"));
	CreateSoundEffect("Stage1BGM", TEXT("Caves Invincible 3.3.wav"));
	CreateSoundEffect("Jump", TEXT("sfx_jump.wav"));
	CreateSoundEffect("Shot", TEXT("sfx_gunshot_01.wav"));

	return true;
}

void JEONG::SoundManager::Update()
{
	m_AudioEngine->Update();
}

void JEONG::SoundManager::AllStop()
{
	m_AudioEngine->Suspend();
}

void JEONG::SoundManager::Restart()
{
	m_AudioEngine->Resume();
}

void JEONG::SoundManager::CreateSoundEffect(const string & KeyName, const wstring & FileName, const string & PathKey)
{
	if (FindSoundEffect(KeyName) != m_NULLPTR1)
		return;
	
	const TCHAR* pPath = PathManager::Get()->FindPath(PathKey);
	wstring	FullPath;

	if (pPath != NULLPTR)
		FullPath = pPath;

	FullPath += FileName;

	unique_ptr<SoundEffect> newSoundEffect = make_unique<SoundEffect>(m_AudioEngine.get(), FullPath.c_str());
	m_SoundEffectMap.insert(make_pair(KeyName, move(newSoundEffect)));
}

void JEONG::SoundManager::CreateBGMList(const string & KeyName, unique_ptr<SoundEffectInstance> instance)
{
	m_SoundEffectInstanceMap.insert(make_pair(KeyName, move(instance)));
}

void JEONG::SoundManager::RemoveBGMList(const string & KeyName)
{
	unordered_map<string, shared_ptr<SoundEffectInstance>>::iterator FindIter = m_SoundEffectInstanceMap.find(KeyName);

	if (FindIter == m_SoundEffectInstanceMap.end())
		return;

	m_SoundEffectInstanceMap.erase(FindIter);
}

shared_ptr<SoundEffect> const & JEONG::SoundManager::FindSoundEffect(const string & KeyName)
{
	unordered_map<string, shared_ptr<SoundEffect>>::iterator FindIter = m_SoundEffectMap.find(KeyName);

	if (FindIter == m_SoundEffectMap.end())
		return m_NULLPTR1;

	return FindIter->second;
}

shared_ptr<SoundEffectInstance> const & JEONG::SoundManager::FindSoundEffectInstance(const string & KeyName)
{
	unordered_map<string, shared_ptr<SoundEffectInstance>>::iterator FindIter = m_SoundEffectInstanceMap.find(KeyName);

	if (FindIter == m_SoundEffectInstanceMap.end())
		return m_NULLPTR2;

	return FindIter->second;
}
