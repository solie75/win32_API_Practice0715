#pragma once

class CObject;
class CImage;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
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
	float m_fAccTime; // ���� ���� �ð�
	float m_fMaxTime; // ���� �ð�

	CAM_EFFECT m_eEffect; // ī�޶� ȿ�� Ÿ��

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


};

