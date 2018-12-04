#include "stdafx.h"
#include "Camera_Com.h"
#include "../GameObject.h"
#include "Transform_Com.h"
JEONG_USING

JEONG::Camera_Com::Camera_Com()
{
	m_ComType = CT_CAMERA;
	m_CameraType = CT_PERSPECTIVE;
	m_Target = NULLPTR;
}

JEONG::Camera_Com::~Camera_Com()
{
}

JEONG::Camera_Com::Camera_Com(const Camera_Com & camera)
	:Component_Base(camera)
{
	m_CameraType = camera.m_CameraType;
	m_View = camera.m_View;
	m_Projection = camera.m_Projection;
	m_Target = NULLPTR;
}

bool JEONG::Camera_Com::Init()
{

	return true;
}

int JEONG::Camera_Com::Input(float DeltaTime)
{
	return 0;
}

int JEONG::Camera_Com::Update(float DeltaTime)
{
	m_View.Identity();

	if (m_Target != NULLPTR)
	{
		Vector3	Move = m_Target->GetDeltaMove();

		if (Move != Vector3::Zero)
			m_Transform->Move(Move);
	}

	//memcpy 41 ~ 43��ġ == Pos��ġ��.
	Vector3 TempPos = m_Transform->GetWorldPos();
	TempPos *= -1.0f;

	memcpy(&m_View[3][0], &TempPos, sizeof(Vector3));

	return 0;
}

int JEONG::Camera_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void JEONG::Camera_Com::Collision(float DeltaTime)
{
}

void JEONG::Camera_Com::CollisionLateUpdate(float DeltaTime)
{
}

void JEONG::Camera_Com::Render(float DeltaTime)
{
}

JEONG::Camera_Com * JEONG::Camera_Com::Clone()
{
	return new Camera_Com(*this);
}

void JEONG::Camera_Com::SetCameraType(CAMERA_TYPE eType)
{
	m_CameraType = eType;

	switch (eType)
	{
		case CT_PERSPECTIVE:
			m_Projection = XMMatrixPerspectiveFovLH(DegreeToRadian(m_ViewAngle), m_Width / m_Height, m_Near, m_Far);
			break;

		case CT_ORTHO:
			/*
			ȭ���� 800 600�̶�� �����Ѵ�. �����ϰ��� 100�̶�� �����Ѵ�.

			(���ؽ� ������)     (�������)
			 0,    0.5, 0, 1	100 0   0 0
			 0.5, -0.5, 0, 1	0   100 0 0
			-0.5, -0.5, 0, 1	0   0   1 0
								100 100 0 1

			(100) = (0 0 * 0) + (1 0 * 1) + (2 0 * 3) + (3 0 * 3)
			(150) = (0 1 * 0) + (1 1 * 1) + (2 1 * 3) + (3 1 * 3)

			������ ������Ŀ� ���� ���ؽ������͸� ����������İ��Ŀ� ��ȯ����.
			100, 150, 0, 1		1/400 0      0 0
			150, 50,  0, 1		0     1/-300 0 0
			50,  50,  0, 1		0     0      1 0
			-1,   1,  1, 1

			���� ��
			-0.75, 0.5
			-0.625, 0.83

			�������� ����
			2/(right-left)      0					0            0
			0					2/(top-bottom)      0            0
			0					0					1/(zf-zn)	 0
			(left+right)/(left-right)  (top+bottom)/(bottom-top)  zn/(zn-zf)
			*/

			//���⼭ Pos�� �������� ����� ���´�. 
			//�׷��� �ε����� �ݴ�� ������� �������� ����� �����ϴ�. (�»������ ��ǥ�� ��������)
			m_Projection = XMMatrixOrthographicOffCenterLH(0.0f, m_Width, 0.0f, m_Height, m_Near, m_Far);
			break;
			//���������� �� ������ ���Ͽ� �������ڴٴ� ��.
	}
}

void JEONG::Camera_Com::SetCameraInfo(CAMERA_TYPE eType, float Width, float Height, float ViewAngle, float Near, float Far)
{
	m_Width = Width;
	m_Height = Height;
	m_Near = Near;
	m_Far = Far;
	m_ViewAngle = ViewAngle;

	SetCameraType(eType);
}

void JEONG::Camera_Com::SetWidth(float Width)
{
	m_Width = Width;
	SetCameraType(m_CameraType);
}

void JEONG::Camera_Com::SetHeight(float Height)
{
	m_Height = Height;
	SetCameraType(m_CameraType);
}

void JEONG::Camera_Com::SetViewAngle(float Angle)
{
	m_ViewAngle = Angle;
	SetCameraType(m_CameraType);
}

void JEONG::Camera_Com::SetNear(float Near)
{
	m_Near = Near;
	SetCameraType(m_CameraType);
}

void JEONG::Camera_Com::SetFar(float Far)
{
	m_Far = Far;
	SetCameraType(m_CameraType);
}

Matrix JEONG::Camera_Com::GetViewMatrix() const
{
	return m_View;
}

Matrix JEONG::Camera_Com::GetProjection() const
{
	return m_Projection;
}

void JEONG::Camera_Com::SetTarget(JEONG::GameObject* pTarget)
{
	m_Target = pTarget->GetTransform();
}

void JEONG::Camera_Com::SetTarget(JEONG::Component_Base* pTarget)
{
	m_Target = pTarget->GetTransform();
}