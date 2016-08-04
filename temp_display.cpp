/*
void Display::DrawBattlefield(Frametype)
{
	std::vector<std::string> *processingFrame = NULL;
	switch (Frametype)
	{
		case FIRST: processingFrame = &m_frame1; break;
		case LAST: processing Frame = &m_frame2;
	}

	processingFrame[0] = "ggg"

	&frame[0] = "######################";
	for (int i = 0; i < BF_SIZE; ++i)
	{
		std::cout << '#';
		for (int j = 0; j < BF_SIZE; ++j)
			{
				if (GetField(i,j) == m_player->GetPosition()) std::cout << '@';
				else m_field[i][j]->Show();
			}
		std::cout << '#' << std::endl;
	}
	std::cout << "######################" << std::endl;
}


void GenerateFrame(std::vector<std::string> *frame);
{
	for (unsigned int frame = 0; frame < FRAMES_COUNT; ++frame)
	{
		DrawBattlefield(frame);
		DrawPlayer(frame);
		if (m_player->HaveTarget()) DrawEnemy(frame);
	}
}


void Display::DrawBattlefield(unsigned int frame)
{
	switch (frame)
	{
		case 1:
			vector<std::string> currentFrame = 
	}
	m_frames[ frame ].push_back(std::endl);
	std::cout << "######################" << std::endl; //BF
	for (int i = 0; i < BF_SIZE; ++i)
	{
		std::cout << '#';
		for (int j = 0; j < BF_SIZE; ++j)
			{
				if (GetField(i,j) == m_player->GetPosition()) std::cout << '@';
				else m_field[i][j]->Show();
			}
		std::cout << '#' << std::endl;
	}
	std::cout << "######################" << std::endl;
}


char Display::DrawField(Field * field, unsigned int frame)
{
	if (!field->IsVisible()) return '.';
	else
	{
		if (field->HaveEnemy())
	 	{
	 	 	if (field->GetEnemy()->GetLevel() == 10) return 'Z';
	 	 	else return (char) field->GetEnemy()->GetLevel();
	 	}

		else if (field != m_player->GetPosition() && field->HaveItem()) return '*';
		else if (field == m_player->GetPosition() && field->HaveItem())
		{
			if (frame == 0) return '@';
			if (frame == 1) return '*';
		}
		else return ' ';
	}
}


	std::cout << "TARGET MONSTER:" << std::endl;	//MONSTER
	std::cout << "Name: " << m_name << std::endl;
	std::cout << "Level: " << m_level << std::endl;
	std::cout << "Damage: " << m_damage << std::endl;
	std::cout << "HP: " << m_HP << "/" << m_maxHP << std::endl;
	std::cout << Game::ShowBar(m_HP, m_maxHP) << std::endl << std::endl;

	std::cout << "Name: " << m_name << std::endl;   //Player
	std::cout << "Level: " << m_level << std::endl;
	std::cout << "Damage: " << m_damage << std::endl;
	std::cout << "HP: " << m_HP << "/" << m_maxHP << std::endl;
	std::cout << Game::ShowBar(m_HP, m_maxHP) << std::endl;
	std::cout << "Mana: " << m_mana << "/" << m_maxMana << std::endl;
	std::cout << Game::ShowBar(m_mana, m_maxMana) << std::endl;
	std::cout << "Exp: " << m_exp << "/" << m_expMax << std::endl;
	std::cout << Game::ShowBar(m_exp, m_expMax) << std::endl << std::endl;
	if (m_target != NULL) m_target->GetEnemy()->Show();
}


void Display::ShowCurrentFrame () const
{

}


std::string Display::ShowBar(int current, int max) const
{
	int num;
	std::string result = "[";
	num = (current != 0 ? (int)( (double)current / max * BARWIDTH) : 0);
	for (int i = 0; i < num; ++i) result += '#';
	for (int i = 0; i < BARWIDTH - num; ++i) result += '.';
	result += ']';
	return result;
}




printw ("######################\n");
for (int i = 0; i < 20; ++i) {
       printw ("#");
       for (int j = 0; j < 20; ++j)
               this->field[i][j]->Show();
       printw ("#\n");
}
printw ("######################\n");



mvprintw(2, 25, "Name: %s", this->name.c_str());
mvprintw(3, 25, "Level: %d", this->level);
mvprintw(4, 25, "HP: %d/%d %s", this->HP, this->maxHP, Game::ShowBar(this->HP, this->maxHP).c_str());
mvprintw(5, 25, "Mana: %d/%d %s", this->mana, this->maxMana, Game::ShowBar(this->mana, this->maxMana).c_str());
mvaddch(this->coordRow + 1, this->coordCol + 1, '@');
*/
