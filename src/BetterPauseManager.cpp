#include "pch.h"
#include "BetterPauseManager.h"

bool BetterPauseManager::init() {
	m_sFileName = "CCBetterPauseManager.dat";
	m_pSwitchPause = { "SwitchPause", 1 };
	m_pSwitchQuest = { "SwitchQuest", 1 };
	m_pSwitchButtonsPos = { "SwitchButtonsPos", 1 };

	this->setup();

	return true;
}

void BetterPauseManager::encodeListTo(DS_Dictionary* data, const ListData& list) {
	if (!data->stepIntoSubDictWithKey(list.m_sTitle)) {
		data->setSubDictForKey(list.m_sTitle);
		data->stepIntoSubDictWithKey(list.m_sTitle);
	}
	data->setStringArrayForKey("entries", list.m_vEntries);
	data->setIntegerForKey("offset", list.m_uOffset);
	data->setIntegerForKey("index", list.m_uIndex);
	data->stepOutOfSubDict();
}

bool BetterPauseManager::loadListFrom(DS_Dictionary* data, ListData& list) {
	if (!data->stepIntoSubDictWithKey(list.m_sTitle)) {
		return false;
	}
	list.m_vEntries = data->getStringArrayForKey("entries");
	list.m_uOffset = data->getIntegerForKey("offset");
	list.m_uIndex = data->getIntegerForKey("index");
	//handle error checking in GUI class.

	data->stepOutOfSubDict();

	return true;
}

void BetterPauseManager::encodeDataTo(DS_Dictionary* data) {
	//data->setStringForKey("version", VERSION);

	//this->encodeListTo(data, m_dAll);
	//this->encodeListTo(data, m_dApplied);
	this->encodeListTo(data, m_pSwitchPause);
	this->encodeListTo(data, m_pSwitchQuest);
	this->encodeListTo(data, m_pSwitchButtonsPos);

	//data->setBoolForKey("reloadSFX", m_bReloadSFX);
	//data->setBoolForKey("reloadMusic", m_bReloadMusic);
	//data->setBoolForKey("checkPlists", m_bCheckPlists);
	//data->setBoolForKey("checkQuality", m_bCheckQuality);
	//data->setBoolForKey("enhanceQuality", m_bEnhanceQuality);
}

void BetterPauseManager::dataLoaded(DS_Dictionary* data) {
	if (!this->loadListFrom(data, m_pSwitchPause) ||
		!this->loadListFrom(data, m_pSwitchQuest) ||
		!this->loadListFrom(data, m_pSwitchButtonsPos)) {
		this->firstLoad();
		return;
	}

	//m_bReloadSFX = data->getBoolForKey("reloadSFX");
	//m_bReloadMusic = data->getBoolForKey("reloadMusic");
	//m_bCheckPlists = data->getBoolForKey("checkPlists");
	//m_bCheckQuality = data->getBoolForKey("checkQuality");
	//m_bEnhanceQuality = data->getBoolForKey("enhanceQuality");
}

void BetterPauseManager::firstLoad() {
	m_pSwitchPause.m_vEntries = { "Better Pause", "AG. Pause", "Normal Pause", "Simple Pause"};
	m_pSwitchPause.m_uOffset = 0;
	m_pSwitchQuest.m_vEntries = { "Full", "Button", "Disable" };
	m_pSwitchQuest.m_uOffset = 0;
	m_pSwitchButtonsPos.m_vEntries = { "Left", "Right" };
	m_pSwitchButtonsPos.m_uOffset = 0;
}

void BetterPauseManager::syncVectors(const std::vector<std::string>& other, unsigned int& added, unsigned int& removed) {
	
}

BetterPauseManager* BetterPauseManager::sharedState() {
	if (!shareStateVariable) {
		shareStateVariable = new BetterPauseManager();
		shareStateVariable->init();
	}

	return shareStateVariable;
}

VariableA& sharedStateBP() {
	static VariableA inst;
	return inst;
}

void VariableA::LoadSettings() {
	auto file = fopen((Utils::GetAppdataDirGD() + std::string("betterPause2.data")).c_str(), "rb");
	if (file) {
		fseek(file, 0, SEEK_END);
		auto size = ftell(file);
		if (size == sizeof(sharedStateBP())) {
			fseek(file, 0, SEEK_SET);
			fread(&sharedStateBP(), sizeof(sharedStateBP()), 1, file);
			fclose(file);
		}
	}
}

void VariableA::SaveSettings() {
	auto file = fopen((Utils::GetAppdataDirGD() + std::string("betterPause2.data")).c_str(), "wb");
	if (file) {
		fwrite(&sharedStateBP(), sizeof(sharedStateBP()), 1, file);
		fclose(file);
	}
}