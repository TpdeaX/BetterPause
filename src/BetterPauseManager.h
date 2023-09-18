#pragma once
#ifndef __BETTERPAUSEMANAGER__
#define __BETTERPAUSEMANAGER__

#include "pch.h"
#include "BetterPause.h"

class BetterPauseManager : public gd::GManager {
protected:
	static inline BetterPauseManager* shareStateVariable = nullptr;

public:
	ListData m_pSwitchPause;
	ListData m_pSwitchQuest;
	ListData m_pSwitchButtonsPos;

protected:
	virtual bool init();

	virtual void encodeDataTo(DS_Dictionary* data);
	virtual void dataLoaded(DS_Dictionary* data);
	virtual void firstLoad();

	void syncVectors(const std::vector<std::string>& other, unsigned int& added, unsigned int& removed);

	inline void encodeListTo(DS_Dictionary* data, const ListData& list);
	inline bool loadListFrom(DS_Dictionary* data, ListData& list);

public:
	static BetterPauseManager* sharedState();
};

#endif

struct VariableA {
	int posQuickASafe[6] = { -2, 0, 1, 10, 14, 38 };
	int posQuickA[6] = { -2, 0, 1, 10, 14, 38 };
	void LoadSettings();
	void SaveSettings();
};

VariableA& sharedStateBP();
