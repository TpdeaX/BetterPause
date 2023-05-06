#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <gd.h>

namespace gd {

	class CCSpritePlus;

	// jesus fucking christ (painfully written by @hjfod)
	//modifier es velocidad we
	enum GameObjectType {
		kGameObjectTypeSolid = 0,
		kGameObjectTypeHazard = 2,
		kGameObjectTypeInverseGravityPortal = 3,
		kGameObjectTypeNormalGravityPortal = 4,
		kGameObjectTypeShipPortal = 5,
		kGameObjectTypeCubePortal = 6,
		kGameObjectTypeDecoration = 7,
		kGameObjectTypeYellowJumpPad = 8,
		kGameObjectTypePinkJumpPad = 9,
		kGameObjectTypeGravityPad = 10,
		kGameObjectTypeYellowJumpRing = 11,
		kGameObjectTypePinkJumpRing = 12,
		kGameObjectTypeGravityRing = 13,
		kGameObjectTypeInverseMirrorPortal = 14,
		kGameObjectTypeNormalMirrorPortal = 15,
		kGameObjectTypeBallPortal = 16,
		kGameObjectTypeRegularSizePortal = 17,
		kGameObjectTypeMiniSizePortal = 18,
		kGameObjectTypeUfoPortal = 19,
		kGameObjectTypeModifier = 20,
		kGameObjectTypeSecretCoin = 22,
		kGameObjectTypeDualPortal = 23,
		kGameObjectTypeSoloPortal = 24,
		kGameObjectTypeSlope = 25,
		kGameObjectTypeWavePortal = 26,
		kGameObjectTypeRobotPortal = 27,
		kGameObjectTypeTeleportPortal = 28,
		kGameObjectTypeGreenRing = 29,
		kGameObjectTypeCollectible = 30,
		kGameObjectTypeUserCoin = 31,
		kGameObjectTypeDropRing = 32,
		kGameObjectTypeSpiderPortal = 33,
		kGameObjectTypeRedJumpPad = 34,
		kGameObjectTypeRedJumpRing = 35,
		kGameObjectTypeCustomRing = 36,
		kGameObjectTypeDashRing = 37,
		kGameObjectTypeGravityDashRing = 38,
		kGameObjectTypeCollisionObject = 39,
		kGameObjectTypeSpecial = 40,
	};

	class GJSpriteColor;
	class ColorActionSprite;
	class GJEffectManager;

	class GJSpriteColor;
	class ColorActionSprite;
	class GJEffectManager;

	#pragma runtime_checks("s", off)
	class GDH_DLL GameObject : public CCSpritePlus /* 0x1f0 */ {
	public:
		bool m_bUnk3;				// 0x1f0
		bool m_bIsBlueMaybe;		// 0x1f1
		float m_fUnk2;				// 0x1f4
		float m_fUnk;				// 0x1f8
		float m_fUnk3;				// 0x1fc
		float m_fUnk4;				// 0x200
		bool m_bUnk;				// 0x204
		float m_fAnimSpeed2;		// 0x208
		bool m_bIsEffectObject;		// 0x20c
		bool m_bRandomisedAnimStart;// 0x20d
		float m_fAnimSpeed;			// 0x210
		bool m_bBlackChild;			// 0x214
		bool m_bUnkOutlineMaybe;	// 0x215
		float m_fBlackChildOpacity;	// 0x218
		bool field_21C;	// 0x21c
		bool m_bEditor;	// 0x21d
		bool m_bGroupDisabled;	// 0x21e
		bool m_bColourOnTop;	// 0x21f
		int m_baseColorID; //0x27c on macos
		int m_detailColorID;
		bool m_baseColorHSVModified;
		bool m_detailColorHSVModified;
		cocos2d::CCPoint m_startPosOffset;
		float m_rotateOffset;
		bool m_tintTrigger;
		bool m_isFlippedX;
		bool m_isFlippedY;
		cocos2d::CCPoint m_boxOffset;
		bool m_isOriented;
		cocos2d::CCPoint m_boxOffset2;
		OBB2D* m_objectOBB2D;
		bool m_oriented;
		cocos2d::CCSprite* m_glowSprite;
		bool m_notEditor;
		cocos2d::CCAction* m_myAction;
		bool m_unk1;
		bool m_runActionWithTag;
		bool m_objectPoweredOn;
		cocos2d::CCSize m_objectSize;
		bool m_modifier;
		bool m_active;
		bool m_animationFinished;
		cocos2d::CCParticleSystemQuad* m_particleSystem;
		std::string m_effectPlistName;
		bool m_particleAdded;
		bool m_hasParticles;
		bool m_unkCustomRing;
		cocos2d::CCPoint m_portalPosition;
		bool m_unkParticleSystem;
		cocos2d::CCRect m_objectTextureRect;
		bool m_textureRectDirty;
		float m_rectXCenterMaybe;
		cocos2d::CCRect m_objectRect2;
		bool m_isObjectRectDirty;
		bool m_isOrientedRectDirty;
		bool m_hasBeenActivated;
		bool m_hasBeenActivatedP2;
		bool m_hasDetailColor;
		bool m_isPulseStick;
		int m_linkedGroup;
		bool m_isSaw;
		int m_customRotateSpeed;
		bool m_sawIsDisabled;
		bool m_unknownVisibility345;
		bool m_unknown346;
		bool m_unknownVisibility347;
		cocos2d::CCSprite* m_baseSprite;
		cocos2d::CCSprite* m_detailSprite;//0x294
		PAD(0x4);
		float m_objectRadius;//0x2EC
		bool m_isRotatedSide;//0x2F0
		float m_unk2F4;
		float m_unk2F8;
		int m_uniqueID;
		GameObjectType m_nObjectType;
		int m_section;
		bool m_touchTriggered;
		bool m_spawnTriggered;
		cocos2d::CCPoint m_startPosition;
		std::string m_textureName;
		bool m_useAudioScale;
		bool m_sleeping;
		float m_rotation;
		cocos2d::CCSize m_obStartScale;
		bool m_startFlipX;
		bool m_startFlipY;
		bool m_shouldHide;
		float m_spawnXPosition;
		bool m_invisible;
		float m_enterAngle;
		int m_activeEnterEffect;
		int m_parentMode;
		bool m_isGlowDisabled;
		int m_targetColorID;
		float m_scale;
		int m_nObjectID;
		int m_unknown3c8;
		bool m_unk368;
		bool m_unk369;
		bool m_unk36A;
		bool m_isDontEnter;
		bool m_isDontFade;
		int m_defaultZOrder;
		bool m_useSecondSheet;
		bool m_isPortal;
		bool m_lockColourAsChild;
		bool m_customAudioScale;
		int m_minAudioScale;
		int m_maxAudioScale;
		bool m_unkParticleSystem2;
		int m_secretCoinID;
		int m_unkUnusedSaveStringKey53;
		bool m_invisibleMode;
		bool m_glowUserBackgroundColour;
		bool m_useSpecialLight;
		bool m_orbOrPad;
		float m_glowOpacityMod;
		bool m_upSlope;
		int m_slopeType;
		float m_slopeAngle;
		bool m_hazardousSlope;
		float m_realOpacity;
		GJSpriteColor* m_baseColor;
		GJSpriteColor* m_detailColor;
		int m_unknown420;
		ZLayer m_defaultZLayer;
		ZLayer m_zLayer;
		int m_gameZOrder;
		std::string m_textObjectString;
		bool m_showGamemodeBorders;
		bool m_unk3D9;
		bool m_isSelected;
		int m_globalClickCounter;
		PAD(0x8);
		bool m_shouldUpdateColorSprite;
		float m_multiScaleMultiplier;
		bool m_isGroupParent;
		short* m_groups;
		short m_groupCount;
		short* m_pulseGroups;
		short m_pulseGroupCount; // mac 0x470
		short* m_alphaGroups;
		short m_alphaGroupCount; // mac 0x480
		int m_editorLayer;
		int m_editorLayer2;
		int m_unk414;
		PAD(0xC);
		cocos2d::CCPoint m_firstPosition;
		PAD(0x15);
		bool m_isTriggerable;
		PAD(0x6);
		bool m_highDetail;
		ColorActionSprite* m_colorActionSpriteBase;
		ColorActionSprite* m_colorActionSpriteDetail;
		GJEffectManager* m_effectManager;
		PAD(0xC);
		bool m_orbMultiActivate;

		//CCNode vtable
		virtual void setScaleX(float scale) {
			return reinterpret_cast<void(__thiscall*)(GameObject*, float)>(
				base + 0xE5050
				)(this, scale);
		}
		virtual void setScaleY(float scale) {
			return reinterpret_cast<void(__thiscall*)(GameObject*, float)>(
				base + 0xE50E0
				)(this, scale);
		}
		virtual void setScale(float scale) {
			return reinterpret_cast<void(__thiscall*)(GameObject*, float)>(
				base + 0xE5170
				)(this, scale);
		}
		virtual void setVisible(bool visible) {
			return reinterpret_cast<void(__thiscall*)(GameObject*, bool)>(
				base + 0xE57C0
				)(this, visible);
		}
		virtual void setRotation(float rotation) {
			return reinterpret_cast<void(__thiscall*)(GameObject*, float)>(
				base + 0xE4ED0
				)(this, rotation);
		}
		virtual bool initWithTexture(cocos2d::CCTexture2D* texture) {
			return reinterpret_cast<bool(__thiscall*)(GameObject*, cocos2d::CCTexture2D*)>(
				base + 0xCFA80
				)(this, texture);
		}
		virtual void setChildColor(const cocos2d::ccColor3B& color) {
			return reinterpret_cast<void(__thiscall*)(GameObject*, const cocos2d::ccColor3B&)>(
				base + 0xEE900
				)(this, color);
		}

		//CCRGBAProtocol vtable
		virtual void setOpacity(GLubyte opacity) {
			return reinterpret_cast<void(__thiscall*)(GameObject*, GLubyte)>(
				base + 0xE53C0
				)(this, opacity);
		}

		static GameObject* createWithKey(int key) {
			return reinterpret_cast<GameObject* (__fastcall*)(int)>(
				base + 0xcf4f0
				)(key);
		}
		static GameObject* createWithFrame(const char* frame) {
			return reinterpret_cast<GameObject* (__fastcall*)(const char*)>(
				base + 0xCF8F0
				)(frame);
		}
		static GameObject* objectFromString(std::string str, bool unknown) {
			auto pRet = reinterpret_cast<GameObject* (__fastcall*)(std::string, bool)>(
				base + 0xEBE50
				)(str, unknown);
			__asm add esp, 0x18
			return pRet;
		}

		void deselectObject() {
			this->m_isSelected = false;

			return reinterpret_cast<void(__fastcall*)(GameObject*)>(
				base + 0xeee50
			)(this);
		}

		std::string getSaveString() {
			std::string ret;

			reinterpret_cast<void(__thiscall*)(GameObject*, std::string*)>(
				base + 0xed0c0
			)(
				this, &ret
			);

			return ret;
		}

		void addToGroup(int id) {
			reinterpret_cast<void(__thiscall*)(
				GameObject*, int
			)>(
				base + 0xeb8d0
			)(
				this, id
			);
		}

		void removeFromGroup(int id) {
			reinterpret_cast<void(__thiscall*)(
				GameObject*, int
			)>(
				base + 0xeb930
			)(
				this, id
			);
		}

		cocos2d::CCPoint getBoxOffset() {
			return *reinterpret_cast<cocos2d::CCPoint*(__thiscall*)(
				GameObject*
			)>(base + 0xef350)(this);
		}

		cocos2d::CCPoint getStartPosition() { return m_startPosition; }
		void setStartPosition(cocos2d::CCPoint const& p) { m_startPosition = p; }
		
		unsigned int getUniqueID() { return m_uniqueID; }
		short getGroupID(int ix) { return m_groups[ix]; }
		short getGroupIDCount() { return m_groupCount; }
		std::vector<short> getGroupIDs() {
			std::vector<short> res;

			if (m_groups && m_groups[0])
				for (auto i = 0; i < m_groupCount; i++)
					res.push_back(m_groups[i]);
		
			return res;
		}
		int getGameZOrder() { return m_gameZOrder; }
		void setGameZOrder(int z) { m_gameZOrder = z; }
		void setGameObjType(GameObjectType t) { m_nObjectType = t; }

		GJSpriteColor* getBaseColor() { return m_baseColor; }
		GJSpriteColor* getDetailColor() { return m_detailColor; }
		
		void updateCustomScale(float scale) {
			__asm movss xmm1, scale;
			reinterpret_cast<void(__thiscall*)(GameObject*)>(base + 0xe5340)(this);
		}
		// this is actually a virtual but i cant be bothered to get it in the right place
		void setRScale(float scale) {
			reinterpret_cast<void(__thiscall*)(GameObject*, float)>(base + 0xe5280)(this, scale);
		}
		void setObjectColor(const cocos2d::ccColor3B& color) {
			reinterpret_cast<void(__thiscall*)(GameObject*, const cocos2d::ccColor3B&)>(base + 0xee620)(this, color);
		}
		void selectObject(const cocos2d::ccColor3B& color = { 0, 255, 0 }) {
			reinterpret_cast<void(__thiscall*)(GameObject*, const cocos2d::ccColor3B)>(base + 0xee960)(this, color);
		}

		cocos2d::CCRepeatForever* createRotateAction(float f, int n) {
			__asm movss xmm1, f

			auto pRet = reinterpret_cast<cocos2d::CCRepeatForever*(__thiscall*)(GameObject*, int)>(
				base + 0xe49b0
			)(this, n);

			return pRet;
		}

		void setMyAction(cocos2d::CCAction* pAction) {
			return reinterpret_cast<void(__thiscall*)(GameObject*, cocos2d::CCAction*)>(
				base + 0xd1b90
			)(this, pAction);
		}


		void activateObject(PlayerObject* player) {
			reinterpret_cast<void(__thiscall*)(GameObject*, PlayerObject*)>(base + 0xEF0E0)(this, player);
		}

		virtual void customSetup() {
			reinterpret_cast<void(__thiscall*)(GameObject*)>(base + 0xd1c10)(this);
		}

		virtual void powerOnObject() {
			reinterpret_cast<void(__thiscall*)(GameObject*)>(base + 0xe5d40)(this);
		}

		void commonSetup() {
			reinterpret_cast<void(__thiscall*)(GameObject*)>(base + 0xcfac0)(this);
		}


		void destroyObject() {
			reinterpret_cast<void(__thiscall*)(GameObject*)>(base + 0xE5D80)(this);
		}

		cocos2d::CCRect const& getObjectRect()
		{
			return *reinterpret_cast<cocos2d::CCRect * (__thiscall*)(
				GameObject*
				)>(base + 0xE4A40)(this);
		}
		cocos2d::CCRect getObjectRect(float a, float b)
		{
			cocos2d::CCRect r = getObjectRect();
			r.origin.x += a * r.size.width * 1.5f;
			r.origin.y += b * r.size.height * 1.5f;
			r.size.width *= a;
			r.size.height *= b;
			return r;
		}

		virtual cocos2d::CCRect getObjectRect2(float f1, float f2) {
			return reinterpret_cast<cocos2d::CCRect(__thiscall*)(GameObject*, float, float)>(base + 0xe4b90)(this, f1, f2);
		}
		virtual cocos2d::CCRect const& getObjectTextureRect() {
			return reinterpret_cast<cocos2d::CCRect(__thiscall*)(GameObject*)>(base + 0xe4c40)(this);
		}

		float getObjectRadius() {
			float radius = m_objectRadius;
			if (m_scale != 1.0f)
				radius *= m_scale;
			return radius;
		}

		GameObjectType getType()
		{
			return reinterpret_cast<GameObjectType(__thiscall*)(
				GameObject*
				)>(base + 0x989E0)(this);
		}

		void updateOrientedBox() {
			return reinterpret_cast<void(__thiscall*)(
				GameObject*
				)>(base + 0xef1c0)(this);
		}

		void deactivateObject(bool restart) {
			reinterpret_cast<GameObjectType(__thiscall*)(
				GameObject*, bool
				)>(base + 0xd19b0)(this, restart);
		}


	};

	
	#pragma runtime_checks("s", restore)
}

#endif