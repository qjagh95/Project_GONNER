#pragma once

JEONG_BEGIN

//스태틱 변수만 모아놓은 클래스.
class JEONG_DLL CountManager
{
public:
	int m_LifeCount;
	int m_BulletCount;

public:
	CLASS_IN_SINGLE(CountManager)
};

JEONG_END