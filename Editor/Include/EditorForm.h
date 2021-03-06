#pragma once
#include <Component/Stage2D_Com.h>


// EditorForm 폼 뷰입니다.
JEONG_USING
class MonsterEdit;
class EditScene;
class EditorForm : public CFormView
{
	DECLARE_DYNCREATE(EditorForm)

protected:
	EditorForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~EditorForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EDIT };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CString m_TagName;
	int m_TileCountX;
	int m_TileCountY;
	int m_TileSizeX;
	int m_TileSizeY;
	int m_StartPosX;
	int m_StartPosY;

	GameObject* m_StageObject;
	Stage2D_Com* m_StageCom;
	Transform_Com* m_StageTransform;

	int m_BackColorR;
	int m_BackColorG;
	int m_BackColorB;
	int m_BackColorA;

	BOOL m_isLine;
	MonsterEdit* m_MobTool;
	EditScene* m_EditScene;
	static bool m_isOpenTool;

	GameObject* GetStageObject() const { return m_StageObject; }
	Stage2D_Com* GetStageComponent() const { return m_StageCom; }
	Transform_Com* GetStageTransform() const { return m_StageTransform; }

	void AddWorkText(const wstring& Text, int Index = 0);
	void AddWorkText(const string& Text, int Index = 0);
	void AddWorkText(const CString& Text, int Index = 0);
	void AddWorkText(wchar_t* Text, int Index = 0);
	void AddWorkText(char* Text, int Index = 0);

	void SaveStage(CString FileName);
	void LoadStage(CString FileName);

	CComboBox m_TileTypeBox;
	CComboBox m_TileOptionBox;
	CComboBox m_TileImageBox;
	CListBox m_WorkList;

	CEdit m_StartPosXControl;
	CEdit m_StartPosYControl;
	CEdit m_StartPosZControl;

	CEdit m_Range1Edit;
	CEdit m_Range2Edit;

	CImage m_TileImage;
	wstring m_Path;

	int m_TextCount;
	bool m_isImageLoad;

	CString m_ImageName;
	int m_CreateTileCount;
	int m_TileAngle;

	BOOL m_isRandomTile;
	int m_RandomRange1;
	int m_RandomRange2;

	STAGE2D_TILE_TYPE GetTileType() const;
	TILE2D_OPTION GetTileOption() const;

	virtual void OnDraw(CDC* pDC);
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeTileselect();
	afx_msg void OnCbnSelchangeTileoptionselect();
	afx_msg void OnCbnSelchangeTileimageselect();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedTilecreatebutton();

	afx_msg void OnBnClickedColorsave();

	afx_msg void OnEnChangeColorr();
	afx_msg void OnEnChangeColorg();
	afx_msg void OnEnChangeColorb();
	afx_msg void OnEnChangeColora();
	afx_msg void OnEnChangeTilecountx();
	afx_msg void OnEnChangeTilecounty();
	afx_msg void OnEnChangeTilesizex();
	afx_msg void OnEnChangeTilesizey();
	afx_msg void OnBnClickedTileclear();

	afx_msg void OnBnClickedLineon();
	afx_msg void OnBnClickedTileload();
	afx_msg void OnBnClickedTilesave();
	afx_msg void OnEnChangeCreatetilecount();

	afx_msg void OnEnChangeTilerotation();

	afx_msg void OnBnClickedCheck1();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedToolopen();
};


