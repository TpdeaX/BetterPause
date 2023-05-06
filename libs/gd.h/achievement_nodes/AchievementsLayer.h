#ifndef __ACHIEVEMENTLAYER_H__
#define __ACHIEVEMENTLAYER_H__

#include <gd.h>

namespace gd {

	class GJDropDownLayer;

	class GDH_DLL AchievementsLayer : public GJDropDownLayer {
	public:
		void customSetup() {
			reinterpret_cast<void(__thiscall*)(AchievementsLayer*)>(
				base + 0x3c2f0
				)(this);
		}
		void loadPage(int pag) {
			reinterpret_cast<void(__thiscall*)(AchievementsLayer*, int)>(
				base + 0x3c600
				)(this, pag);
		}
	};
}

#endif