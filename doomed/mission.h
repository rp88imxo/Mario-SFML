int getCurrentMission(int x)
{
	if (x < 300)
		return 0;
	if ((x > 300) && (x < 800))
		return 1;
}

std::string getTextMission(int mission)
{
	std::string missionText;
	switch (mission)
	{
	case 0: missionText = "   Добро пожаловать в игру\n   Твоя цель - собирать двери\n   Будь внимателен -\n   Время ограниченно!"; break;
	case 1: missionText = "   Движение - W,A,S,D\n   Информация отображается в левом верхнем углу"; break;
	}
	return missionText;
}