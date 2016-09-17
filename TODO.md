# asciidunge
Small ascii roguelike game
*ncurses-based console "Desktop Dungeon" clone*

## Internal TO-DO list:
- make enemy spawning more sparse
- refactor member functions for more name consistency
- make all counters as single array
- fix non-showing victory bug!

## Latest changes
+ refactor Player/Powerup classes
+ fix 100% CPU load bug!
+ make powerups - hp, mana and damage!
+ make future fight calculations store in BF class member variables
+ add switching frames with current fight state and future state
+ add future fight calculation on enemy select
+ move Fight() and CalculateFutureFight() to "Battlefield" class
+ add Battlefield.playerCopy and Battlefield.enemyCopy pointers 
+ change all unsigned int to uint8
+ added first strike priority based on level comparison
+ Implemented separate Player::Fight() function
+ added class destructors
+ Display::LevelUpCheck() / Display::LevelUpCheckEnd() functions implemented
+ Display::SendEvent(EventType) {LVLUP,MONSTER_DEATH, ...} implemented
+ Player::m_display property is used to get access to display instance

