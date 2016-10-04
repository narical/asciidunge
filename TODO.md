# asciidunge
Small ascii roguelike game
*ncurses-based console "Desktop Dungeon" clone*

Next milestone: v0.5a
target game state:

- [x] 8 different monsters with different "perks":
 - [x] skeleton - weak in any way
 - [x] goblin - high damage, low hp
 - [x] troll - fat
 - [x] rogue - first strike
 - [x] zombie
 - [x] mage
 - [X] golem
 - [x] ghost

- [ ] 5 different items
 - [x] Sword of Readiness - grants first strike
 - [ ] Fireball - deals damage based on player level
 - [ ] Mighty Strike - add 30% damage bonus to next strike
 - [ ] Heal - healing player based on it's level
 - [ ] Energy shield - incoming damage goes to mana first

- [x] 3 powerup types
 - [x] health powerup - gives 1 hp per character level, scales with level-up
 - [x] mana powerup - gives 1 mana permanently, doesn't scales
 - [x] damage powerup - gives 10% cumulative damage bonus

## Internal TO-DO list:
- [ ] refactor abstraction layers
- [ ] make enemy spawning more sparse
- [ ] add items recycling

## Latest changes
- [x] separate items to different files and move them to 'items' directory
- [x] make items spawn only once
- [x] move all monster files to separate directory
- [x] add items using (sword only)
- [x] add items droping
- [x] add items picking
- [x] add items
- [x] add inventory
- [x] change powerup calculations entirely
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
