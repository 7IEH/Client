#pragma once

class CObject;

class CCamera
{
public:
	SINGLE(CCamera);

private:
	vec2						m_vLookAt;		// ī�޶� ���� �ٶ󺸴� ��ġ
	vec2						m_vCurLookAt;  // ���� ��ġ�� ���� ��ġ ���� ��ġ
	vec2						m_vPrevLookAt;		// ī�޶� ���� ���������� ��ġ
	CObject*				m_pTargetObj;	// ī�޶� Ÿ�� ������Ʈ

	vec2						m_vDiff;				// �ػ� �߽���ġ��, ī�޶� LookAt ���� ���� ��

	float						m_fTime;				// Ÿ���� ���󰡴µ� �ɸ��� �ð�
	float						m_fSpeed;			// Ÿ���� ���󰡴� �ӵ�
	float						m_fAccTime;      // ���� �ð�
public:
	void SetLookAt(vec2 _vLook) 
	{
		m_vLookAt = _vLook;
		float fMoveDist=(m_vLookAt - m_vPrevLookAt).Length();
		m_fSpeed=fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	}
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	vec2 GetLookAt() { return m_vCurLookAt; }
	vec2 GetRenderPos(vec2 _vObjPos) { return _vObjPos - m_vDiff; }
	vec2 GetRealPos(vec2 _vRenderPos) { return _vRenderPos + m_vDiff;  }

public:
	void update();

private:
	void CalDiff();
};

