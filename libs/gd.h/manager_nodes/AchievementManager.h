#ifndef __ACHIEVEMENTMANAGER_H__
#define __ACHIEVEMENTMANAGER_H__

#include <gd.h>

namespace gd {
	class GDH_DLL AchievementManager : public cocos2d::CCNode {
	protected:
		PAD(16);
		cocos2d::CCDictionary* m_pAchievements;
		PAD(4);

	public:
		static AchievementManager* sharedState() {
			return reinterpret_cast<AchievementManager* (__stdcall*)()>(
				base + 0x7B10
				)();
		}

		void getAchievementsWithID(int ID) {
			reinterpret_cast<void(__thiscall*)(AchievementManager*, int)>(
				base + 0x82D0
				)(this, ID);
		}
	};
}

#endif