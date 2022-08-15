#pragma once

class CObject;


class CEventMgr
{
	SINGLE(CEventMgr);

private:
	vector<tEventInfo> m_vecEvent;
	vector<CObject*> m_vecDeadObject;
public:
	void EventMgrTick();
	void AddEvent(const tEventInfo& _event)
	{
		m_vecEvent.push_back(_event);
	}
};

