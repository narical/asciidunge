# asciidunge
Small ascii roguelike game
*ncurses-based console "Desktop Dungeon" clone*

## Internal TO-DO list:
- [ ] refactor abstraction layers
- [ ] use player level as hp per powerup and 1 for mana powerup
- [ ] make enemy spawning more sparse
- [ ] add Player.powerup_count for different calculation


## Latest changes
- [x] make next level exp 5 times more then current level
- [x] add initiative property to player and monsters
- [x] add mana regeneration by 1 per tile
- [x] add healing by player level per tile
- [x] remove ExtractHP/Mana from fields
- [x] set sight radius to 8 neightbour fields near player
- [x] make all mosters of different types
- [x] move to CMake build system
- [x] make all counters as single array
- [x] move all constants to config.h
- [x] change uint8_t to uint16_t where needed
- [x] clean all #includes
- [x] fix player spawning on powerup
- [x] remove vectors entirely
- [x] make all members' names begin with _ instead of m_
- [x] refactor Player/Powerup classes
- [x] fix 100% CPU load bug!
- [x] make powerups - hp, mana and damage!
- [x] make future fight calculations store in BF class member variables
- [x] add switching frames with current fight state and future state
- [x] add future fight calculation on enemy select
- [x] move Fight() and CalculateFutureFight() to "Battlefield" class
- [x] add Battlefield.playerCopy and Battlefield.enemyCopy pointers 
- [x] change all unsigned int to uint8
- [x] added first strike priority based on level comparison
- [x] Implemented separate Player::Fight() function
- [x] added class destructors
- [x] Display::LevelUpCheck() / Display::LevelUpCheckEnd() functions implemented
- [x] Display::SendEvent(EventType) {LVLUP,MONSTER_DEATH, ...} implemented
- [x] Player::m_display property is used to get access to display instance
