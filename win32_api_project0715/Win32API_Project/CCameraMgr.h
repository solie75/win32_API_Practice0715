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
	float m_fAccTime; // 누적 진행 시간
	float m_fDuration; // 이펙트 총 재생 시간 
	CAM_EFFECT m_eEffect; // 카메라 효과 타입
};

class CCameraMgr
{
	SINGLE(CCameraMgr);

private:
	// 현제 카메라가 보고있는 좌표
	Vec m_vResolution; // 화면 해상도
	Vec m_vLook; // 현재 카메라가 보고있는 좌표
	Vec m_vDiff; // 화면 해상도 중심 좌표와 카메라 Look 간의 차이

	CObject* m_pTargetObj;

	// veil
	CImage* m_pVeil; // 가림막 용도  BitmapImage 생성
	float m_fAlpha; // 투명 강도

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

		//m_eEffect = _type; // 어떤 효과인지
		//m_fAccTime = 0; // 카메라 효과 시작시에 누적 진행 시간은 0이다.
		//m_fDuration = _fDuration; // 총 걸리는 시간
	}


};

