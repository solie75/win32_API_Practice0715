#pragma once

class CObject;
class CImage;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

struct CameraEffectInfo
{
	float m_fAccTime; // ���� ���� �ð�
	float m_fDuration; // ����Ʈ �� ��� �ð� 
	CAM_EFFECT m_eEffect; // ī�޶� ȿ�� Ÿ��
};

class CCameraMgr
{
	SINGLE(CCameraMgr);

private:
	// ���� ī�޶� �����ִ� ��ǥ
	Vec m_vResolution; // ȭ�� �ػ�
	Vec m_vLook; // ���� ī�޶� �����ִ� ��ǥ
	Vec m_vDiff; // ȭ�� �ػ� �߽� ��ǥ�� ī�޶� Look ���� ����

	CObject* m_pTargetObj;

	// veil
	CImage* m_pVeil; // ������ �뵵  BitmapImage ����
	float m_fAlpha; // ���� ����

	list<CameraEffectInfo> m_CameraEffectInfoList;

public:
	void CameraMgrInit();
	void CameraMgrTick();
	void CameraMgrRender(HDC _dc);
public:
	Vec GetRenderPos(Vec _vRealPos)
	{
		return (_vRealPos - m_vDiff);
	}

	void SetTargetObject(CObject* _pObj)
	{
		m_pTargetObj = _pObj;
	}

	void SetCameraEffect(CAM_EFFECT _type, float _fDuration)
	{
		CameraEffectInfo info = {};
		info.m_eEffect = _type;
		info.m_fDuration = _fDuration;

		m_CameraEffectInfoList.push_back(info);

		//m_eEffect = _type; // � ȿ������
		//m_fAccTime = 0; // ī�޶� ȿ�� ���۽ÿ� ���� ���� �ð��� 0�̴�.
		//m_fDuration = _fDuration; // �� �ɸ��� �ð�
	}


};

