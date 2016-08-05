# asciidunge
Small ascii roguelike game
*ncurses-based console "Desktop Dungeon" clone*

## Internal TO-DO list:

* make Player::m_display property to get access to display instance
* make Display::SendEvent(EventType) method where EventType = {LVLUP,MONSTER_DEATH, ...}
* make class destructors
* make Display::LevelUpCheck() and Display::LevelUpCheckEnd() functions with attron/off
* move fight to standalone function
* make player and enemy colors depend of %HP remaining
