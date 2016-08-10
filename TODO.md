# asciidunge
Small ascii roguelike game
*ncurses-based console "Desktop Dungeon" clone*

## Internal TO-DO list:

## Latest changes
+ add future fight calculation on enemy select
+ change all unsigned int to uint8
+ added first strike priority based on level comparison
+ Implemented separate Player::Fight() function
+ added class destructors
+ Display::LevelUpCheck() / Display::LevelUpCheckEnd() functions implemented
+ Display::SendEvent(EventType) {LVLUP,MONSTER_DEATH, ...} implemented
+ Player::m_display property is used to get access to display instance

