# asciidunge
Small ascii roguelike game
*ncurses-based console "Desktop Dungeon" clone*

## Internal TO-DO list:
* implement copy/assignment operator for Player and Enemy classes
* make fight prediction
* change all unsigned int to uint8

## Latest changes
+ Player::m_display property is used to get access to display instance
+ Display::SendEvent(EventType) {LVLUP,MONSTER_DEATH, ...} implemented
+ Display::LevelUpCheck() / Display::LevelUpCheckEnd() functions implemented
+ added class destructors
+ Implemented separate Player::Fight() function
+ added first strike priority based on level comparison

