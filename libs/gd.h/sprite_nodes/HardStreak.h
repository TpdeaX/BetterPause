#ifndef __HARDSTREAK_H__
#define __HARDSTREAK_H__

#include <gd.h>

namespace gd {
    class GDH_DLL HardStreak : public cocos2d::CCDrawNode {
        public:

			virtual bool init() {
				reinterpret_cast<void(__thiscall*)(HardStreak*)>(gd::base + 0x14e430)(this);
			}
			void addPoint(cocos2d::CCPoint point) {
				reinterpret_cast<void(__thiscall*)(HardStreak*, cocos2d::CCPoint)>(gd::base + 0x14ebc0)(this, point);
			}
			void clearBehindXPos(float) {

			}
			static HardStreak* create() {
				return reinterpret_cast<HardStreak*(__thiscall*)()>(gd::base + 0x14e390)();
			}
			void firstSetup() {
				reinterpret_cast<void(__thiscall*)(HardStreak*)>(gd::base + 0x14e490)(this);
			} 
			double normalizeAngle(double d) {

			}
			cocos2d::CCPoint quadCornerOffset(cocos2d::CCPoint pointX, cocos2d::CCPoint pointY, float offset) {

			}
			void reset() {
				
			}
			void resumeStroke() {

			}
			void stopStroke() {
				reinterpret_cast<void(__thiscall*)(HardStreak*)>(gd::base + 0x14e460)(this);
			}
			void updateStroke(float dt) {
				reinterpret_cast<void(__thiscall*)(HardStreak*, float)>(gd::base + 0x14e530)(this, dt);
			}

			float m_p1;
			int m_p2;
			int m_p3;
			bool m_isFill;
			PAD(0x3);
			cocos2d::CCArray* m_pointsArr;
			cocos2d::CCPoint m_currentPoint;
			float m_waveSize;
			float m_pulseSize;
			bool m_isSolid;


    };
}

#endif