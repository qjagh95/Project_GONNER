#include "stdafx.h"
#include "SoundManager.h"

JEONG_USING
SINGLETON_VAR_INIT(SoundManager)

shared_ptr<SoundEffect> SoundManager::m_NULLPTR1;
shared_ptr<SoundEffectInstance> SoundManager::m_NULLPTR2;

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

bool SoundManager::Init()
{
	AUDIO_ENGINE_FLAGS Flag = AudioEngine_Default;
#ifdef _DEBUG
	Flag = Flag | AudioEngine_Debug;
#endif
	m_AudioEngine = make_unique<AudioEngine>(Flag);

	CreateSoundEffect("LogoBGM", TEXT("Over the top (short intro).wav"));
	CreateSoundEffect("StageBGM1", TEXT("Caves Invincible 3.3.wav"));
	CreateSoundEffect("StageBGM2", TEXT("Deaths jam 3.0.wav"));
	CreateSoundEffect("StageBGM3", TEXT("Deaths jam 3.0.wav"));
	CreateSoundEffect("StageBGM4", TEXT("Deaths jam 3.0.wav"));
	CreateSoundEffect("Jump", TEXT("sfx_jump.wav"));
	CreateSoundEffect("Shot", TEXT("sfx_gunshot_01.wav"));
	CreateSoundEffect("Button", TEXT("sfx_button_crunch01.wav"));
	CreateSoundEffect("BugEffect", TEXT("BugEffect.wav"));
	CreateSoundEffect("BugChange", TEXT("BugChange.wav"));
	CreateSoundEffect("BulletColl", TEXT("BulletColl.wav"));
	CreateSoundEffect("EatGun", TEXT("EatGun.wav"));
	CreateSoundEffect("Reload", TEXT("Reload.wav"));
	CreateSoundEffect("HeartEat", TEXT("HeartEat.wav"));
	CreateSoundEffect("ReloadBulletCreate", TEXT("ReloadBulletCreate.wav"));
	CreateSoundEffect("DelayFinish", TEXT("DelayFinish.wav"));
	CreateSoundEffect("LifeEat", TEXT("LifeEat.wav"));
	CreateSoundEffect("MonsterDie", TEXT("sfx_death_test_01.wav"));
	CreateSoundEffect("DieBoom", TEXT("DieBoom.wav"));
	CreateSoundEffect("ChangeStateBug", TEXT("ChangeStateBug.wav"));
	CreateSoundEffect("JumpAttack", TEXT("JumpAttack.wav"));
	CreateSoundEffect("SnakeEat", TEXT("SnakeEat.wav"));
	CreateSoundEffect("SnakeOut", TEXT("SnakeOut.wav"));

	return true;
}

void SoundManager::Update()
{
	m_AudioEngine->Update();
}

void SoundManager::AllStop()
{
	m_AudioEngine->Suspend();
}

void SoundManager::Restart()
{
	m_AudioEngine->Resume();
}

void SoundManager::CreateSoundEffect(const string & KeyName, const wstring & FileName, const string & PathKey)
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

void SoundManager::CreateBGMList(const string & KeyName, unique_ptr<SoundEffectInstance> instance)
{
	m_SoundEffectInstanceMap.insert(make_pair(KeyName, move(instance)));
}

void SoundManager::RemoveBGMList(const string & KeyName)
{
	unordered_map<string, shared_ptr<SoundEffectInstance>>::iterator FindIter = m_SoundEffectInstanceMap.find(KeyName);

	if (FindIter == m_SoundEffectInstanceMap.end())
		return;

	m_SoundEffectInstanceMap.erase(FindIter);
}

shared_ptr<SoundEffect> const & SoundManager::FindSoundEffect(const string & KeyName)
{
	unordered_map<string, shared_ptr<SoundEffect>>::iterator FindIter = m_SoundEffectMap.find(KeyName);

	if (FindIter == m_SoundEffectMap.end())
		return m_NULLPTR1;

	return FindIter->second;
}

shared_ptr<SoundEffectInstance> const & SoundManager::FindSoundEffectInstance(const string & KeyName)
{
	unordered_map<string, shared_ptr<SoundEffectInstance>>::iterator FindIter = m_SoundEffectInstanceMap.find(KeyName);

	if (FindIter == m_SoundEffectInstanceMap.end())
		return m_NULLPTR2;

	return FindIter->second;
}
