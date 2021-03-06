#pragma once
#include "stdafx.h"

#define JEONG_BEGIN namespace JEONG {
#define JEONG_END }

JEONG_BEGIN

enum GAME_MODE
{
	GM_2D,
	GM_3D,
};

enum COMPONENT_TYPE
{
	CT_NONE,
	CT_TRANSFORM,
	CT_RENDER,
	CT_MATERIAL,
	CT_ANIMATION2D,
	CT_CAMERA,
	CT_FREECAMERA,
	CT_UI,
	CT_COLLIDER,
	CT_TITLEBAR,
	CT_TEXT,
	CT_TILE2D,
	CT_TILEIMAGE,
	CT_STAGE2D,
	CT_BACKCOLOR,
	CT_GARVITY,
	CT_NUMBER,
	CT_BUTTON,
	CT_GRAVITY,
	CT_GUNITEM,
	CT_MONSTER,
	CT_EDITOR,
	CT_GONNER,
	CT_SNAKEHEAD,
	CT_MAX,
};

//각 축의 방향
enum AXIS
{
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
	AXIS_MAX,
};

enum CBUFFER_SHADER_TYPE
{
	CST_VERTEX = 0x1,
	CST_PIXEL = 0x2,
};

enum CAMERA_TYPE
{
	CT_PERSPECTIVE,
	CT_ORTHO,
};

enum RENDER_STATE
{
	RS_BLEND,
	RS_RASTERIZER,
	RS_DEPTHSTENCIL,
	RS_END
};

enum ANIMATION2D_TYPE
{
	A2D_ATLS,
	A2D_FRAME,
};

enum ANIMATION_OPTION
{
	AO_LOOP,
	AO_ONCE_DESTROY,
	AO_ONCE_STOP,
};

enum COLLIDER_TYPE
{
	CT_RECT,
	CT_POINT,
	CT_CIRCLE,
	CT_OBB2D,
	CT_PIXEL,
};

enum COLLSION_CALLBACK_TYPE
{
	CCT_FIRST,
	CCT_DOING,
	CCT_END,
	CCT_MAX,
};

enum UI_TYPE
{
	UT_PANNAL,
	UT_BUTTON,
	UT_CHECKBOX,
	UT_RADIOBUTTON,
	UT_BAR,
	UT_ICON,
	UT_ICONSLOT,
};

enum BUTTON_STATE
{
	BS_DISABLE,
	BS_NORMAL,
	BS_MOUSEOVER,
	BS_CLICK,
	BS_MAX,
};

enum CHECKBOX_STATE
{
	CBS_NORMAL,
	CBS_TRUE,
	CBS_OVER,
	CBS_FALSE,
	CBS_MAX,
};

enum BAR_DIR
{
	BD_LEFT,
	BD_RIGHT,
	BD_UP,
	BD_DOWN,
};

enum RADIO_DIR
{
	RD_DOWN,
	RD_RIGHT,
};

enum TRANSFORM_PARENT_FLAG
{
	TPF_SCALE = 0x1,
	TPF_ROT = 0x2,
	TPF_POS = 0x4
};

enum STAGE2D_TILE_TYPE
{
	STT_NONE,
	STT_TILE,
	STT_ISO,
};

enum RENDER_GROUP
{
	RG_LANDSCAPE,
	RG_NORMAL,
	RG_ALPHA1,
	RG_ALPHA2,
	RG_ALPHA3,
	RG_UI,
	RG_HUD,
	RG_END
};

enum TILE2D_OPTION
{
	T2D_NORMAL,
	T2D_NOMOVE,
};

enum LOGO_ALPHABAT
{
	LA_A,
	LA_R,
	LA_T,
	LA_I,
	LA_N,
	LA_H,
	LA_E,
	LA_SPACAL,
};

enum FADE_OPTION
{
	FO_IN,
	FO_OUT,
	FO_INOUT,
};

enum MOVE_DIR
{
	MD_LEFT,
	MD_RIGHT,
};

enum MENU_ENEMY_TYPE
{
	ME_M1,
	ME_M2,
	ME_M3,
	ME_M4,
	ME_M5,
	ME_M6,
	ME_M7,
	ME_M8,
	ME_M9,
	ME_M10,
	ME_M11,
	ME_M12,
	ME_M13,
	ME_M14,
	ME_M15,
};

enum TOOL_OBJECT_TYPE
{
	TOT_GUNITEM,
	TOT_HEART,
	TOT_BOX,
	TOT_SNAKEHEAD,
	TOT_SNAKTAIL,
	TOT_M1,
	TOT_M2,
	TOT_M3,
	TOT_M4,
	TOT_M5,
};

enum GUN_STATE
{
	GGS_IDLE,
	GGS_SHOT,
	GGS_RELOAD,
	GGS_MAX,
};

enum MONSTER_TYPE
{
	MT_GUARD,
	MT_TRACE,
	MT_BASIC,
	MT_AIRDOWN,
	MT_REFLECT,
	MT_MAX,
};

enum GUARD_STATE
{
	GUS_IDLE,
	GUS_MOVE,
	GUS_HIT,
	GUS_GUARD,
	GUS_GUARDDOWN,
	GUS_MAX,
};

enum BASIC_STATE
{
	BSM_IDLE,
	BSM_MOVE,
	BSM_HIT,
	BSM_MAX,
};

enum AIRDOWN_STATE
{
	AIR_IDLE,
	AIR_HIT,
	AIR_UP,
	AIR_DOWN,
	AIR_MAX,
};

enum TRACE_STATE
{
	TRS_IDLE,
	TRS_MOVE,
	TRS_TRACE,
	TRS_HIT,
	TRS_MAX,
};

enum REFLACT_STATE
{
	RS_IDLE,
	RS_ATTACK,
	RS_HIT,
	RS_MAX,
};

JEONG_END