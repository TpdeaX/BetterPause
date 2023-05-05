#pragma once
#include "pch.h"

namespace Utils {

	static auto proc = GetCurrentProcess();
	static auto libcocos_base = reinterpret_cast<std::uintptr_t>(GetModuleHandleA("libcocos2d.dll"));
	static auto fmod_base = reinterpret_cast<std::uintptr_t>(GetModuleHandleA("fmod.dll"));
	static auto toasted_base = reinterpret_cast<std::uintptr_t>(GetModuleHandleA("ToastedMarshmellow.dll"));
	static auto tBot_base = reinterpret_cast<std::uintptr_t>(GetModuleHandleA("tBot.dll"));

	const char* getNameObj(cocos2d::CCNode* obj);

	gd::GameManager* shareManager();
	gd::PlayLayer* getplayLayerA();
	cocos2d::CCDirector* shareDirectorA();
	cocos2d::CCSize winSize();
	GLubyte convertOpacitySimplf(float opaTM);
	gd::FMODAudioEngine* shareFMOD();
	gd::GameSoundManager* shareManagerSound();

	//PlayLayer
	cocos2d::ccColor3B primaryIndex();
	cocos2d::ccColor3B secondaryIndex();
	float getPercentageReversePerXpos();
	float getPercentageReversePerTime();
	float getPercentagePerXpos();
	float getPercentagePerTime();
	float getPercentageNow();
	float getPercentageReverseNow();
	float getPercentageNowFix();
	float getPercentageReverseNowFix();

	cocos2d::ccColor3B shiftHue(cocos2d::ccColor3B& color, int shift, int max, int min);
	cocos2d::CCSequence* rainbowInit(float duration);
	cocos2d::CCSequence* rainbowPastelInit(float duration);
	void ResetColorAndStopRainbow(cocos2d::CCNodeRGBA*& obj, cocos2d::_ccColor3B color);
	void RainbowSelectA(bool ranN, bool ranP, cocos2d::CCNodeRGBA* obj, float durationranN, float durationranP, cocos2d::ccColor3B colorReset);
	bool direxist(const char* szPath);
	std::string GetAppdataDir();
	std::string GetCurrentDirectoryZ();
	std::string GetAppdataDirGD();
	std::string GetFolderMusicCurrent();
	bool getLastVersionGDHM();
	void copyToClipboardAggr(const char* text);
	std::string getIDCSW(cocos2d::CCNode* self);
	std::string convertChartoString(char* c);
	std::string convertConstChartoString(const char* c);
	tm* getRTimeCurrent();
	void getPosCursorAggregates();
	int retAdressGDHM(int i);
	bool getModsMemoryExt(int i);
	int getCheatIndicatorState();
	cocos2d::ccColor3B getcolorCheatNow();
	const char* getCCSwitchIntFloat(const char* txtFloat, const char* txtInt, float nf, bool isAcurr);
	std::string getFontWithFormat(std::uint8_t select);
	std::string getFontWithFormatOriginal(std::uint8_t select);
	int getMaxZOrdenInLayer(cocos2d::CCLayer* self);
	bool returnZeroBool(int i);
	bool nameChildFind(cocos2d::CCNode* node, const char* name);
	void findLayerAndProcessC(bool hide, cocos2d::CCLayer* layer, const char* nameLayer, bool usingLayer);
	void findLayerAndProcessEnabled(bool enabled, cocos2d::CCLayer* layer, const char* nameLayer);
	void PlayLayer_getTestModeLabel(gd::PlayLayer* self);
	template <typename T, typename U>
	size_t get_offset(U T::* member);
	std::string getPerStrConeAcurr(const char* txt);
	bool FindPercentageFixDecimal(char* text);
	float perStartCallOp(int ret);
	float convertXposToPercentage(float xPos);
	template <typename E>
	void pop_back_SafeList(std::list<E>& list) {
		if (list.size() > 0) {
			list.pop_back();
		}
	}
	template <typename F>
	void assing_back_SafeList(F& value, std::list<F>& list) {
		if (list.size() > 0) {
			value = list.back();
		}
	}

	template <typename G, typename H>
	void assing_back_VectorSecondSafe(H value, std::vector<std::pair<G, H>>& vector) {
		if (vector.size() > 0) {
			vector.back().second = value;
		}
	}

	gd::GJBaseGameLayer* getGJBaseGameLayer();
	bool* topLeftSwitch(std::uint8_t sel);
	cocos2d::CCPoint getPosLayerLabelsTopButtom(std::uint8_t sel);
	bool isLabelEmpty(cocos2d::CCLabelProtocol* label);
	std::vector<std::uint8_t> getPositionAggregatesLabelsA();
	std::vector<std::uint8_t> getFntSelectLabelsAggregatesStatusA();
	std::vector<float> getSizeSelectLabelsAggregatesStatusA();
	std::vector<float> getOpacitySelectLabelsAggregatesStatusA();
	std::vector<bool> getVisibilityLabelsAggregates();
	std::vector<bool> getRainbowLabelsAggregates();
	std::vector<bool> getRainbowPastelLabelsAggregates();

	cocos2d::CCLabelBMFont* getLabelObjByTag(int tag);
	char* convert_to_non_const_char(const char* str);
	std::string formatNumberString(std::string format, float firstFloat, float secondFloat);
	std::string getVehicleStateString(gd::PlayerObject* player);
	bool deleteMusicWithID(const char* ID);
	std::string rgbToHex(int r, int g, int b);
	void hexToRgb(std::string hexValue, float& r, float& g, float& b);
	void rgbToHexForAggregates(int i);
	void hexToRgbForAggregates(int i);
	const char* getDifficultyIcon(gd::GJGameLevel* level);
	bool isObjectInVector(const std::vector<std::pair<gd::GameObject*, cocos2d::CCPoint>>& vec, gd::GameObject* obj);
	bool isObjectInVector(const std::vector<std::pair<gd::StartPosObject*, cocos2d::CCPoint>>& vec, gd::GameObject* obj);
}

