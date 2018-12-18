#pragma once
#include <Ready.h>

#include "Component/Animation2D_Com.h"
#include "Component/Collider_Com.h"
#include "Component/Gravity_Com.h"

JEONG_USING

enum GONNER_STATE
{
	GS_BUGIDLE,
	GS_BUGDOWN,
	GS_BUGJUMP,
	GS_IDLE,
	GS_RUN,
	GS_ATTACK,
	GS_JUMP,
	GS_DOUBLEJUMP,
	GS_WALLSTOP,
	GS_KNIGHT,
	GS_MAX,
};

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

	void FS_BUGDOWN(float DeltaTime);
	void FS_BUGIDLE(float DeltaTime);
	void FS_BUGJUMP(float DeltaTime);
	void FS_IDLE(float DeltaTime);
	void FS_RUN(float DeltaTime);
	void FS_ATTACK(float DeltaTime);
	void FS_JUMP(float DeltaTime);
	void FS_DOUBLEJUMP(float DeltaTime);
	void FS_WALLSTOP(float DeltaTime);
	void FS_KNIGHT(float DeltaTime);

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
	Vector3 m_ScaleHalf;
	PlayerUVCBuffer m_CBuffer;
	Vector2 m_WinSize;

	Vector3 m_upPos;
	Vector3 m_downPos;
	Vector3 m_leftPos;
	Vector3 m_rightPos;
	
	Gravity_Com* m_GravityCom;
	Stage2D_Com* m_Stage;

	WaveCBuffer m_WaveCBuffer;

	float m_BugAngle;
	bool m_isBugJump;
	bool m_isDirChangeLeft;
	bool m_isDirChangeRight;

	int m_BugJumpMax;
	int m_BugJumpCount;

	Tile2D_Com* m_downTile;
	Tile2D_Com* m_upTile;
	Tile2D_Com* m_leftTile;
	Tile2D_Com* m_rightTile;

protected:
	Gonner_Com();
	Gonner_Com(const Gonner_Com& userCom);
	~Gonner_Com();

public:
	friend class GameObject;
};

