#pragma once

class CObject;

class CCamera
{
public:
	SINGLE(CCamera);

private:
	vec2						m_vLookAt;		// 카메라가 실제 바라보는 위치
	vec2						m_vCurLookAt;  // 이전 위치와 현재 위치 보정 위치
	vec2						m_vPrevLookAt;		// 카메라가 보는 이전프레임 위치
	CObject*				m_pTargetObj;	// 카메라 타켓 오브젝트

	vec2						m_vDiff;				// 해상도 중심위치와, 카메라 LookAt 간의 차이 값

	float						m_fTime;				// 타겟을 따라가는데 걸리는 시간
	float						m_fSpeed;			// 타겟을 따라가는 속도
	float						m_fAccTime;      // 누적 시간
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

