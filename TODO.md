# asciidunge
Small ascii roguelike game
*ncurses-based console "Desktop Dungeon" clone*

## Internal TO-DO list:
- make all counters as single array
- refactor abstraction layers
- make all pointers variables begin with p
- add assertions to entire code
- move all constants to config.h

- remove ExtractHP/Mana from fields, use new player ManaRegen/HealthRegen properties
- make enemy spawning more sparse
- make different powerup classes
- add initiative property to player and monsters

## Latest changes
+ change uint8_t to uint16_t where needed
+ clean all #includes
+ fix player spawning on powerup
+ remove vectors entirely
+ make all members' names begin with _ instead of m_
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
