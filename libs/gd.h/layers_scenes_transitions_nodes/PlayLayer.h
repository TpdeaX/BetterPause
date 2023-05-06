#ifndef __PLAYLAYER_H__
#define __PLAYLAYER_H__

#include <gd.h>

namespace gd {

	class GJBaseGameLayer;
	class CCCircleWaveDelegate;
	class GameObject;
	class CCMenuItemSpriteExtra;
	// class EndPortalObject;
	using EndPortalObject = GameObject;
	// class AudioEffectsLayer;
	using AudioEffectsLayer = cocos2d::CCLayerColor;
	// class GJGroundLayer;
	class GDH_DLL GJGroundLayer : public cocos2d::CCLayer {
		public:
			void updateGroundWidth() {
				reinterpret_cast<void(__thiscall*)(GJGroundLayer*)>(
					base + 0x12dda0
				)(this);
			}
	};
	class GJGameLevel;
	class GDH_DLL UILayer : public cocos2d::CCLayerColor {
		public:
			PAD(8)
			cocos2d::CCMenu* m_pCheckPointMenu;// 0x1a0
			gd::CCMenuItemSpriteExtra* m_pSpritePauseMenu;

			cocos2d::CCMenu* getMenuPause() {
				return static_cast<cocos2d::CCMenu*>(m_pSpritePauseMenu->getParent());
			}

			void onCheck(CCObject* pSender) {
				reinterpret_cast<void(__thiscall*)(UILayer*, CCObject*)>(
					base + 0x25fb60
				)(this, pSender);
			}

			void onDeleteCheck(CCObject* pSender) {
				reinterpret_cast<void(__thiscall*)(UILayer*, CCObject*)>(
					base + 0x25fc90
				)(this, pSender);
			}

			void onPause(CCObject* pSender) {
				reinterpret_cast<void(__thiscall*)(UILayer*, CCObject*)>(
					base + 0x25fad0
				)(this, pSender);
			}

			bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* evnt) {
				return reinterpret_cast<bool(__thiscall*)(UILayer*, cocos2d::CCTouch*, cocos2d::CCEvent*)>(
					base + 0x25FD20
					)(this, touch, evnt);
			}

			void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* evnt) {
				reinterpret_cast<void(__thiscall*)(UILayer*, cocos2d::CCTouch*, cocos2d::CCEvent*)>(
					base + 0x25fad0
					)(this, touch, evnt);
			}

			inline void toggleCheckpointsMenu(bool toggled) {
				m_pCheckPointMenu->setVisible(toggled);
			}
	};

	class CheckpointObject;
	class EffectGameObject;
	class StartPosObject;

	class GDH_DLL PlayLayer : public GJBaseGameLayer, public CCCircleWaveDelegate {
		public:
			PAD(8);
			unsigned int unk2D8;
			bool unk2DC;
			bool m_bHasCheated; // 0x2DD by taking less than 30s to beat lvl
			int m_dontSaveRand; // 0x2DE random value between 0 and 100 + unk2E8
			int m_dontSaveSeed; // 0x2E2 random value between 0 and 100
			int unk2E8; // 0x2E6
			bool m_debugPauseOff; // opposite of isFrozen
			bool m_shouldSmoothCamera;
			float unused_4e0;
			PAD(4);
			cocos2d::CCObject* unknown4e8;
			float m_camera4f0;
			int unused4f4;
			float m_somegroup4f8;
			float m_groundRestriction; // 0x308
			float m_ceilRestriction;
			bool m_fullReset;
			bool unknown505;
			float unknown508;
			float unknown50c;
			float unknown510;
			float unknown514;
			float unknown518;
			PAD(4);
			StartPosObject* m_startPos; // 0x32C
			CheckpointObject* m_startPosCheckpoint;
			EndPortalObject* m_endPortal; // 0x334
			cocos2d::CCArray* m_checkpoints; // 0x338
			cocos2d::CCArray* m_speedObjects; // 0x33C
			cocos2d::CCArray* unk340;
			cocos2d::CCArray* unk344;
			cocos2d::CCSprite* unk348;
			PAD(8);
			cocos2d::CCArray* unk354;
			cocos2d::CCArray* unk358;
			cocos2d::CCArray* unk35C;
			cocos2d::CCArray* unk360;
			bool m_isMute; // 0x364 has to do with fmod
			PAD(7);
			cocos2d::CCArray* m_screenRingObjects; // 0x36C ring objects that are on screen, yes this is weird
			cocos2d::CCParticleSystemQuad* m_particleSystem;
			cocos2d::CCDictionary* m_pickedUpItems;
			cocos2d::CCArray* m_circleWaves; // 0x378
			cocos2d::CCArray* unk37C;
			AudioEffectsLayer* m_audioEffectsLayer; // 0x380
			PAD(8);
			GJGroundLayer* m_bottomGround; // 0x38C
			GJGroundLayer* m_topGround; // 0x390
			PAD(8);
			bool m_isDead; // 0x39C
			bool m_startCameraAtCorner; // smth to do with the camera
			bool m_cameraYLocked; // set to true when cameraMoveX is called
			bool m_cameraXLocked; // set to true when cameraMoveY is called
			PAD(4);
			int m_ballFrameSeed;
			float unknown5ec;
			float m_lockGroundToCamera;
			float unknown5f4;
			float m_levelLength; // 0x3B4
			float m_realLevelLength;
			cocos2d::CCLabelBMFont* m_attemptLabel; // 0x3BC
			cocos2d::CCLabelBMFont* m_percentLabel; // 0x3C0
			bool m_isCameraShaking; // 0x3C4
			float m_currentShakeStrength; // 0x3C8
			float m_currentShakeInterval; // 0x3CC
			double m_lastShakeTime; // 0x3D0
			cocos2d::CCPoint m_cameraShakeOffset;
			PAD(16);
			bool unk3F0; // always 40
			cocos2d::CCDictionary* m_particleSystemsPlist; // 0x3F4 i really need a better name	 
			cocos2d::CCDictionary* unk3F8;
			cocos2d::CCArray* m_particleSystems; // 0x3FC
			cocos2d::CCNode* unk400;
			cocos2d::CCSprite* m_sliderGrooveSprite; // 0x404
			cocos2d::CCSprite* m_sliderBarSprite; // 0x408
			cocos2d::CCSize m_sliderSize;
			PAD(4);
			int unk418; // always 4
			PAD(8);
			cocos2d::CCArray* m_gravityEffectSprites; // 0x424 contains GravityEffectSprite s	   
			bool unk428;
			bool m_shouldRecordActions; // 0x429 for the hidden rob bot
			bool unk42A;
			bool unk42B; // 0x42B
			bool unk42C;
			bool m_isPlayer2Frozen; // 0x42D wat
			std::string m_previousRecords; // 0x430
			PAD(8);
			double m_time; // 0x450
			PAD(9);
			bool unk461;
			cocos2d::CCDictionary* unk464;
			PAD(8);
			bool m_isPlaybackMode; // 0x470
			PAD(11);
			bool m_isFlipped; // 0x47C
			PAD(3);
			float m_mirrorTransition; // 0x480
			UILayer* m_uiLayer; // 0x484
			GJGameLevel* m_level; // 0x488
			cocos2d::CCPoint m_cameraPosition;
			bool m_isTestMode; // 0x494
			bool m_isPracticeMode; // 0x495
			bool unk496;
			bool unk497;
			cocos2d::CCArray* unk498; // animations array maybe
			bool unk49C;
			PAD(1);
			cocos2d::CCPoint m_playerStartPosition; // 0x4A0
			int m_currentAttempt; // 0x4A8
			int m_jumpCount; // 0x4AC
			bool unk4B0;
			float m_totalTime; // 0x4B4
			int m_attemptJumpCount; // 0x4B8 resets when you die
			bool unk4BC;
			bool m_hasLevelCompleteMenu; // 0x4BD true when the level complete menu shows up, so slightly after completing the lvl
			bool m_hasCompletedLevel; // 0x4BE
			int m_lastDeathPercent; // 0x4C0
			bool unk4C4;
			PAD(11);
			bool unk4D0;
			cocos2d::CCArray* unk4D4;
			cocos2d::CCDictionary* unk4D8;
			PAD(4);
			double unk4E0;
			double unk4E8; // seems to be time modulo 2 for some reason
			PAD(24);
			double unk508; // time again?
			PAD(31);
			bool m_bIsPaused; // 0x52f
			GameObject* m_antiCheatObject;
			bool m_antiCheatPassed;
			bool unk535; // gets set to false when you cheat
			bool m_disableGravityEffect; // 0x536 comes from gv_0072
			PAD(1);

			static PlayLayer* get() { return GameManager::sharedState()->getPlayLayer(); }

			static PlayLayer* create(GJGameLevel* lvl) {
				return reinterpret_cast<PlayLayer*(__fastcall*)(GJGameLevel*)>(
					base + 0x1fb6d0
				)(lvl);
			}

			~PlayLayer() {
				reinterpret_cast<void*(__fastcall*)(PlayLayer*)>(
					base + 0x1fafc0
					)(this);
			}

			static cocos2d::CCScene* scene(GJGameLevel* lvl) {
				return reinterpret_cast<cocos2d::CCScene*(__fastcall*)(GJGameLevel*)>(
					base + 0x1fb690
				)(lvl);
			}

			void showNewBest(bool new_reward, int orbs, int diamonds, bool demon_key, bool unk, bool dont_show_new_best_text) {
				reinterpret_cast<void(__thiscall*)(PlayLayer*, bool, int, int, bool, bool, bool)>(gd::base + 0x1fe3a0)(this, new_reward, orbs, diamonds, demon_key, unk, dont_show_new_best_text);
			}

			void addObject(GameObject* object) {
				reinterpret_cast<void(__thiscall*)(PlayLayer*, GameObject*)>(gd::base + 0x2017e0)(this, object);
			}

			void togglePracticeMode(bool on) {
				reinterpret_cast<void(__thiscall*)(PlayLayer*, bool)>(
					base + 0x20d0d0
				)(this, on);
			}
			void resetLevelW() {
				if (GameManager::sharedState()->getPlayLayer())
					reinterpret_cast<void(__thiscall*)(PlayLayer*)>(gd::base + 0x20BF00)(GameManager::sharedState()->getPlayLayer());
			}
			void resetLevel() {
				reinterpret_cast<void(__thiscall*)(PlayLayer*)>(gd::base + 0x20BF00)(this);
			}
			CheckpointObject* createCheckpoint() {
				return reinterpret_cast<CheckpointObject * (__thiscall*)(PlayLayer*)>(gd::base + 0x20B050)(this);
			}
			void pauseGame() {
				reinterpret_cast<void(__thiscall*)(PlayLayer*)>(gd::base + 0x20D3C0)(this);
			}
			void resumeGame() {
				reinterpret_cast<void(__thiscall*)(PlayLayer*)>(gd::base + 0x20D5C0)(this);
			}
			void normalGame() {
				reinterpret_cast<void(__thiscall*)(PlayLayer*)>(gd::base + 0x20CED0)(this);
			}

			void pickupItem(GameObject* object) {
				reinterpret_cast<void(__thiscall*)(PlayLayer*, GameObject*)>(gd::base + 0x208240)(this, object);
			}// puede que no sea

			void getLastCheckpoint() {
				reinterpret_cast<void(__thiscall*)(PlayLayer*)>(gd::base + 0x20B800)(this);
			}

			void removeLastCheckpoint() {
				reinterpret_cast<void(__thiscall*)(PlayLayer*)>(gd::base + 0x20B830)(this);
			}

			void startMusic() {
				reinterpret_cast<void(__thiscall*)(PlayLayer*)>(gd::base + 0x20C8F0)(this);
			}

			CheckpointObject* removeCheckpoint() {
				return reinterpret_cast<CheckpointObject*(__thiscall*)(PlayLayer*)>(gd::base + 0x20CED0)(this);
			}

			void showRetryLayer() {
				reinterpret_cast<void(__thiscall*)(PlayLayer*)>(gd::base + 0x1FFD40)(this);
			}

			void showRetryLayerW() {
				if(GameManager::sharedState()->getPlayLayer())
					reinterpret_cast<void(__thiscall*)(PlayLayer*)>(gd::base + 0x1FFD40)(GameManager::sharedState()->getPlayLayer());
			}

			void shakeCamera() {
				reinterpret_cast<void(__thiscall*)(PlayLayer*)>(gd::base + 0x1ff210)(this);
			}

			void willSwitchToMode(int mode, PlayerObject* player) {
				reinterpret_cast<void(__thiscall*)(PlayLayer*, int, PlayerObject*)>(gd::base + 0x20A0D0)(this, mode, player);
			}

			void switchToFlyMode(PlayerObject* player, GameObject* portal, bool exit, int mode) {
				reinterpret_cast<void(__thiscall*)(PlayLayer*, PlayerObject*, GameObject*, bool, int)>(gd::base + 0x2097C0)(this, player, portal, exit, mode);
			}

			void animateOutGround(bool idk) {
				reinterpret_cast<void(__thiscall*)(PlayLayer*, bool)>(gd::base + 0x209E60)(this, idk);
			}

			void updateProgressBar() {
				reinterpret_cast<void(__thiscall*)(PlayLayer*)>(gd::base + 0x208020)(this);
			}

			bool checkCollisions(PlayerObject* player) {
				return reinterpret_cast<bool(__thiscall*)(PlayLayer*, PlayerObject*)>(gd::base + 0x203CD0)(this, player);
			}

			void update(float dt) {
				reinterpret_cast<void(__thiscall*)(PlayLayer*, float)>(gd::base + 0x2029C0)(this, dt);
			}

			void syncMusicAfterResume(bool p2) {
				reinterpret_cast<void(__thiscall*)(PlayLayer*, bool)>(gd::base + 0x208800)(this, p2);
			}

			float timeForXPos(float xPos) {
				return reinterpret_cast<float(__thiscall*)(PlayLayer*, float)>(gd::base + 0x2087d0)(this, xPos);
			}

			void destroyPlayer(gd::PlayerObject* player, gd::GameObject* obj) {
				reinterpret_cast<void(__thiscall*)(PlayLayer*, PlayerObject*, GameObject*)>(gd::base + 0x20A1A0)(this, player, obj);
			}

			void playExitDualEffect(PlayerObject* player) {
				reinterpret_cast<void(__thiscall*)(PlayLayer*, PlayerObject*)>(gd::base + 0x208e20)(this, player);
			}

			void onQuit() {
				reinterpret_cast<void(__thiscall*)(PlayLayer*)>(gd::base + 0x20D810)(this);
			}

			void otherplayerWillSwitchMode(gd::PlayerObject* player, gd::GameObject* obj) {
				reinterpret_cast<void(__thiscall*)(PlayLayer*, PlayerObject*, GameObject*)>(gd::base + 0x209540)(this, player, obj);
			}

			void updateDualGround(PlayerObject* player, int mode , bool anim) {
				reinterpret_cast<void(__thiscall*)(PlayLayer*, PlayerObject*, int, bool)>(gd::base + 0x209680)(this, player, mode, anim);
			}

			void toggleDualMode(GameObject* obj, bool b, PlayerObject* player, bool c) {
				reinterpret_cast<void(__thiscall*)(PlayLayer*, GameObject*, bool, PlayerObject*, bool)>(gd::base + 0x208880)(this, obj, b, player, c);
			}

			void toggleFlipped(bool flip, bool instant) {
				reinterpret_cast<void(__thiscall*)(PlayLayer*, bool, bool)>(gd::base + 0x20AB20)(this, flip, instant);
			}

			void playerWillSwitchMode(PlayerObject* player, GameObject* obj) {
				reinterpret_cast<void(__thiscall*)(PlayLayer*, PlayerObject*, GameObject*)>(gd::base + 0x16b290)(this, player, obj);
			} 

			void flipFinished() {
				reinterpret_cast<void(__thiscall*)(PlayLayer*)>(gd::base + 0x20AD10)(this);
			}

			void flipGravity(PlayerObject* player, bool invert, bool instant) {
				reinterpret_cast<void(__thiscall*)(PlayLayer*, bool, bool)>(gd::base + 0x207d30)(this, invert, instant);
			}

			void startGame() {
				reinterpret_cast<void(__thiscall*)(PlayLayer*)>(gd::base + 0x1FD390)(this);
			}

			bool hasUniqueCoin(GameObject* coin) {
				return reinterpret_cast<bool(__thiscall*)(PlayLayer*, GameObject*)>(gd::base + 0x202250)(this, coin);

			}

			void setupLevelStart(gd::LevelSettingsObject* config) {
				reinterpret_cast<void(__thiscall*)(PlayLayer*, LevelSettingsObject*)>(gd::base + 0x20cb60)(this, config);
			}

			void loadFromCheckpoint(gd::CheckpointObject* checkpoint) {
				reinterpret_cast<void(__thiscall*)(PlayLayer*, CheckpointObject*)>(gd::base + 0x20b4a0)(this, checkpoint);
			}

			void updateVisibility() {
				reinterpret_cast<void(__thiscall*)(PlayLayer*)>(gd::base + 0x205460)(this);
			}


	};

	class LevelTools {
	public:
		static void timeForXPos(cocos2d::CCArray* speedArray, int speed) {
			reinterpret_cast<void(__thiscall*)(cocos2d::CCArray*, int)>(gd::base + 0x18AE70)(speedArray, speed);
		}
	};

}

#endif
