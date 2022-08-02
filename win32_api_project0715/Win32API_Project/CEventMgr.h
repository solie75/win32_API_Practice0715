#pragma once

enum class EVENT_TYPE
{
	CREATE_OBJECT, // first : object ptr, second : layer
	DELETE_OBJECT,
	SCENE_CHANGE,

	END,
};

struct tEventInfo
{
	EVENT_TYPE eType;
	DWORD_PTR first;
	DWORD_PTR second;

};



class CEventMgr
{
	SINGLE(CEventMgr);

private:
	vector<tEventInfo> m_vecEvent;
public:
	void EventMgrTick();
	void AddEvent(const tEventInfo& _event)
	{
		m_vecEvent.push_back(_event);
	}
};

