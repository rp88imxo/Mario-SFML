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
	case 0: missionText = "   ����� ���������� � ����\n   ���� ���� - �������� �����\n   ���� ���������� -\n   ����� �����������!"; break;
	case 1: missionText = "   �������� - W,A,S,D\n   ���������� ������������ � ����� ������� ����"; break;
	}
	return missionText;
}