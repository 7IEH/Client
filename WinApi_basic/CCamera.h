#pragma once

class CObject;
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

struct tCamEffect
{
	CAM_EFFECT eEffect;				// ī�޶� ȿ��
	float				m_fDuration;		// ȿ�� �ִ� ���� �ð�
	float				m_fCurTime;		// ī�޶� ȿ�� ���� ����� �ð�
};


class CCamera
{
public:
	SINGLE(CCamera);

private:
	vec2								m_vLookAt;		// ī�޶� ���� �ٶ󺸴� ��ġ
	vec2								m_vCurLookAt;  // ���� ��ġ�� ���� ��ġ ���� ��ġ
	vec2								m_vPrevLookAt;		// ī�޶� ���� ���������� ��ġ

	CObject*						m_pTargetObj;	// ī�޶� Ÿ�� ������Ʈ
	vec2								m_vDiff;				// �ػ� �߽���ġ��, ī�޶� LookAt ���� ���� ��

	float								m_fTime;				// Ÿ���� ���󰡴µ� �ɸ��� �ð�
	float								m_fSpeed;			// Ÿ���� ���󰡴� �ӵ�
	float								m_fAccTime;      // ���� �ð�

	vector<tCamEffect>	m_vecCamEffect;
	CTexture*						m_pVeilTex;			// ī�޶� ������ �ؽ���(����������)

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

	void FadeIn(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_IN;
		ef.m_fDuration = _fDuration;
		ef.m_fCurTime = 0.f;
		m_vecCamEffect.push_back(ef);

		if (0.f == ef.m_fDuration)
			assert(nullptr);
	}
	void FadeOut(float _fDuration) 
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_OUT;
		ef.m_fDuration = _fDuration;
		ef.m_fCurTime = 0.f;
		m_vecCamEffect.push_back(ef);

		if (0.f == ef.m_fDuration)
			assert(nullptr);
	}

public:
	void init();
	void update();
	void render(HDC _dc);

private:
	void CalDiff();
};
