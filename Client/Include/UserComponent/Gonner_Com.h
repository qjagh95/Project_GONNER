#pragma once
#include <Ready.h>

#include "Component/Animation2D_Com.h"
#include "Component/Collider_Com.h"
#include "Component/Gravity_Com.h"

enum GONNER_STATE
{
	GS_BUGIDLE,
	GS_BUGMOVE,
	GS_BUGDOWN,
	GS_IDLE,
	GS_RUN,
	GS_ATTACK,
	GS_JUMP,
	GS_DOUBLEJUMP,
	GS_WALLSTOP,
	GS_KNIGHT,
	GS_MAX,
};

JEONG_USING

class Gonner_Com : public Ready
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	Gonner_Com* Clone() override;

	//void GS_IDLE(float DeltaTime);
	//void GS_RUN(float DeltaTime);
	//void GS_ATTACK(float DeltaTime);
	//void GS_JUMP(float DeltaTime);
	//void GS_DOUBLEJUMP(float DeltaTime);
	//void GS_WALLSTOP(float DeltaTime);
	//void GS_KNIGHT(float DeltaTime);

	void Move(float DeltaTime);
	void BugMove(float DeltaTime);
	void DirCheck();

	void SetStage(Stage2D_Com* stage);
	Stage2D_Com* GetStage() const { return m_Stage; }

private:
	void BasicInit();
	void AnimationInit();

private:
	Animation2D_Com* m_Animation;
	string m_AniName[GS_MAX];
	Vector3 m_Pos;
	Vector3 m_Scale;
	PlayerUVCBuffer m_CBuffer;
	Vector2 m_WinSize;
	
	Gravity_Com* m_GravityCom;
	Stage2D_Com* m_Stage;

	WaveCBuffer m_WaveCBuffer;

protected:
	Gonner_Com();
	Gonner_Com(const Gonner_Com& userCom);
	~Gonner_Com();

public:
	friend class GameObject;
};

