#ifndef __PLAYEROBJECT_H__
#define __PLAYEROBJECT_H__

#include <gd.h>

namespace gd {

	class GameObject;
	class AnimatedSpriteDelegate;
	class GJRobotSprite;
	class GJSpiderSprite;
	class HardStreak;
	class GhostTrailEffect;

	class GDH_DLL PlayerObject : public GameObject, public AnimatedSpriteDelegate {
	public:
		PAD(20);
		bool unk480;
		cocos2d::CCNode* unk484;
		cocos2d::CCDictionary* m_collisionLog;
		cocos2d::CCDictionary* m_collisionLog1;
		PAD(32);
		bool unk4B0;
		cocos2d::CCSprite* unk4B4;
		PAD(28);
		bool unk4D4;
		cocos2d::CCArray* m_particleSystems; // 0x4D8
		bool unk4DC;
		bool m_isHidden; // 0x4DD
		int m_hasGhostTrail; // 0x4E0
		GhostTrailEffect* m_ghostTrail; // 0x4E4
		cocos2d::CCSprite* m_iconSprite;
		cocos2d::CCSprite* m_iconSpriteSecondary;
		cocos2d::CCSprite* m_iconSpriteWhitener;
		cocos2d::CCSprite* m_iconGlow;
		cocos2d::CCSprite* m_vehicleSprite;
		cocos2d::CCSprite* m_vehicleSpriteSecondary;
		cocos2d::CCSprite* unk500;
		cocos2d::CCSprite* m_vehicleSpriteWhitener;
		cocos2d::CCSprite* m_vehicleGlow;
		cocos2d::CCSprite* unk50C;
		cocos2d::CCMotionStreak* m_regularTrail; // 0x510
		HardStreak* m_waveTrail; // 0x514
		double m_xAccel; // 0x518
		double m_jumpAccel; // 0x520
		double m_gravity; // 0x528
		PAD(8);
		bool unk538;
		bool unk539;
		bool unk53A;
		bool unk53B;
		bool m_isInPlayLayer; // 0x53C
		bool unk53D;
		bool unk53E; // is holding on ship idk
		bool unk53F;
		PAD(16);
		double m_lastJumpTime; // 0x550
		double unk558;
		PAD(36);
		float m_decelerationRate;
		PAD(20);
		GameObject* unk59C;
		PAD(8);
		GJRobotSprite* robotSprite;
		GJSpiderSprite* spiderSprite;
		bool unk5B0;
		cocos2d::CCParticleSystemQuad* unk5B4;//0x5b4
		cocos2d::CCParticleSystemQuad* unk5B8;
		cocos2d::CCParticleSystemQuad* unk5BC;
		cocos2d::CCParticleSystemQuad* unk5C0;
		cocos2d::CCParticleSystemQuad* unk5C4;
		cocos2d::CCParticleSystemQuad* unk5C8;
		cocos2d::CCParticleSystemQuad* unk5CC;
		PAD(4);
		cocos2d::CCParticleSystemQuad* unk5D4;
		cocos2d::CCParticleSystemQuad* unk5D8;
		PAD(32);
		bool unk5FC;
		bool unk5FD;
		bool m_bDropping;
		PAD(17);
		bool unk610;// 0x610
		bool m_isHolding; // 0x611
		bool m_hasJustHeld; // 0x612
		bool m_isHolding2; // 0x613 why are there 2 mr robert
		bool m_hasJustHeld2; // 0x614
		int unk618;
		float unk61C;
		int unk620; // always 213
		bool m_canRobotJump; // 0x624
		double m_yAccel; // 0x628
		bool unk630;
		bool unk631;
		float unk634;
		bool m_isShip; // 0x638
		bool m_isBird; // 0x639 ufo
		bool m_isBall; // 0x63A
		bool m_isDart; // 0x63B wave
		bool m_isRobot; // 0x63C
		bool m_isSpider; // 0x63D
		bool m_isUpsideDown; // 0x63E
		PAD(1);
		bool m_isOnGround; // 0x640
		bool m_isDashing; // 0x641
		float m_vehicleSize; // 0x644
		float m_playerSpeed; // 0x648
		cocos2d::CCPoint unk64C; // last pos idk
		cocos2d::CCPoint m_lastPortalPos; // 0x654
		cocos2d::CCLayer* unk65C;
		bool m_isSliding; // 0x660
		bool m_isRising; // 0x661
		bool m_isLocked;
		cocos2d::CCPoint m_lastGroundedPos; // 0x664
		cocos2d::CCArray* m_touchingRings; // 0x66C
		GameObject* m_lastActivatedPortal; // 0x670
		bool m_unk674;
		bool m_unk675;
		cocos2d::ccColor3B m_playerColor1;
		cocos2d::ccColor3B m_playerColor2;
		cocos2d::CCPoint m_position; // 0x67C
		bool unk684;
		bool unk685;
		double unk688;
		PAD(8);
		float m_groundHeight; // 0x698
		float unk69C; // seems to be y vel, cant directly change it though
		PAD(4);
		float unk6A4[200]; // last 200 Y positions, tf
		PAD(28);

		static PlayerObject* create(int cubeFrame, int shipFrame, cocos2d::CCLayer* layer) {
			auto ret = reinterpret_cast<PlayerObject * (__vectorcall*)(int, int, cocos2d::CCLayer*)>(
				base + 0x1e6cf0
				)(cubeFrame, shipFrame, layer);
			
			__asm add esp, 0x4

			return ret;
		}

		bool init(int cubeFrame, int shipFrame, cocos2d::CCLayer* layer) {
			return reinterpret_cast<bool(__thiscall*)(PlayerObject*,int, int, cocos2d::CCLayer*)>(
				base + 0x1e6da0
				)(this, cubeFrame, shipFrame, layer);
		}
		
		virtual void setVisible(bool visible) {
			return reinterpret_cast<void(__thiscall*)(PlayerObject*, bool)>(
				base + 0x1FA860
				)(this, visible);
		}

		void setColor(cocos2d::_ccColor3B const& color) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, cocos2d::_ccColor3B)>(base + 0x1F77F0)(this, color);
		}


		void setSecondColor(cocos2d::_ccColor3B* const& color) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, cocos2d::_ccColor3B*)>(base + 0x1F7870)(this, color);
		}

		void resetStreak() {
			reinterpret_cast<void(__thiscall*)(PlayerObject*)>(base + 0x1E8D50)(this);
		}

		void pushButton(int button) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, int)>(base + 0x1F4E40)(this, button);
		}
		void releaseButton(int button) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, int)>(base + 0x1F4F70)(this, button);
		}
		bool playerIsFalling() {
			return reinterpret_cast<bool(__thiscall*)(PlayerObject*)>(base + 0x1f5d60)(this);
		}
		void runRotateAction() {
			reinterpret_cast<void(__thiscall*)(PlayerObject*)>(base + 0x1e9bf0)(this);
		}
		void playBurstEffect() {
			reinterpret_cast<void(__thiscall*)(PlayerObject*)>(base + 0x1f6790)(this);
		}
		void spiderTestJump(bool param1) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, bool)>(base + 0x1ed360)(this, param1);
		}
		void incrementJumps() {
			reinterpret_cast<void(__thiscall*)(PlayerObject*)>(base + 0x1e9a20)(this);
		}
		void flipGravity(bool param1, bool param2) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, bool, bool)>(base + 0x1f59d0)(this, param1, param2);
		}
		void runNormalRotation() {
			reinterpret_cast<void(__thiscall*)(PlayerObject*)>(base + 0x1e9c50)(this);
		}
		void runBallRotation() {
			reinterpret_cast<void(__thiscall*)(PlayerObject*)>(base + 0x1e9d10)(this);
		}
		void activateStreak() {
			reinterpret_cast<void(__thiscall*)(PlayerObject*)>(base + 0x1f9080)(this);
		}

		void* initPre() {
			return reinterpret_cast<void*(__thiscall*)(PlayerObject*)>(base + 0x1E6650)(this);
		}

		void switchedToMode(gd::GameObjectType type){
			reinterpret_cast<void(__thiscall*)(PlayerObject*, gd::GameObjectType)>(base + 0x1f6f70)(this, type);
		}

		void touchedObject(GameObject* obj) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, GameObject*)>(base + 0x1F6FE0)(this, obj);
		}

		void toggleBirdMode(bool enabled) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, bool)>(base + 0x1f6050)(this, enabled);
		}
		void toggleDartMode(bool enabled) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, bool)>(base + 0x1f62c0)(this, enabled);
		}
		void toggleFlyMode(bool enabled) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, bool)>(base + 0x1f5e40)(this, enabled);
		}
		void toggleGhostEffect(int type) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, int)>(base + 0x1f8930)(this, type);
		}
		void togglePlayerScale(bool enabled) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, bool)>(base + 0x1f9640)(this, enabled);
		}
		void toggleRobotMode(bool enabled) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, bool)>(base + 0x1f6a10)(this, enabled);
		}
		void toggleRollMode(bool enabled) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, bool)>(base + 0x1f68e0)(this, enabled);
		}
		void toggleSpiderMode(bool enabled) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, bool)>(base + 0x1f6cb0)(this, enabled);
		}

		void playerDestroyed(bool isEffect) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, bool)>(base + 0x1efaa0)(this, isEffect);
		}

		void copyAttributes(PlayerObject* player) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, PlayerObject*)>(base + 0x1f93f0)(this, player);

		}

		virtual void update(float dt) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, float)>(base + 0x1e8200)(this, dt);
		}

		void updateSpecial() {
			reinterpret_cast<void(__thiscall*)(PlayerObject*)>(base + 0x1e8ab0)(this);
		}

		//0x22e660 touchObjectInMac

		void func_1() {
			reinterpret_cast<void(__thiscall*)(
				PlayerObject*
				)>(base + 0x1f78e0)(this);
		}

		void resetObject() {
			reinterpret_cast<void(__thiscall*)(
				PlayerObject*
				)>(base + 0x1EECD0)(this);
		}

		void updateRotation() {
			reinterpret_cast<void(__thiscall*)(PlayerObject*)>(base + 0x1ebc00)(this);
		}

		void updateCheckpointTest() {
			reinterpret_cast<void(__thiscall*)(PlayerObject*)>(base + 0x1e8b50)(this);
		}

		void func_2() {
			reinterpret_cast<void(__thiscall*)(PlayerObject*)>(base + 0x1f9a20)(this);
		}

		void updatePlayerScale() {
			reinterpret_cast<void(__thiscall*)(PlayerObject*)>(base + 0x1f9200)(this);
		}

	};
}


#endif