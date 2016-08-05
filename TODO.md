# asciidunge
Small ascii roguelike game
*ncurses-based console "Desktop Dungeon" clone*

## Internal TO-DO list:

+ make Player::m_display property to get access to display instance
+ make Display::SendEvent(EventType) method where EventType = {LVLUP,MONSTER_DEATH, ...}
+ make Display::LevelUpCheck() and Display::LevelUpCheckEnd() functions with attron/off
+ make class destructors
- make player and enemy colors depend of %HP remaining (poor color support in ncurses)
* move fight to standalone function

