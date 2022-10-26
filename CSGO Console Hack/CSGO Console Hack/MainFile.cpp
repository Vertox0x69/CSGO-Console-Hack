#include "Includes.h"


int main()
{
	switch (Content)
	{
		SetConsoleTitleA("Console Hack");
	case 0:
		if ((Content == 0))
		{
			system("color 2");
			std::cout << "Welcome to a free nigga hack!" << std::endl;
			std::cout << "[1] FOV Changer\n[2] BunnyHop Hack\n[3] Glow ESP\n[4] TriggerBot\n[5] RadarHack\n[6] ThirdPerson Mode\n[7] Anti Flashbang" << std::endl;
			std::cout << "Please choose a hack to continue" << std::endl;
			std::cout << "Your choice: ";
			std::cin >> Content;
		}
	case 1:
		if ((Content == 1))
		{
			system("cls");
			std::cout << "Tab number "<<Content<<" has been selected\nLoading it up.." << std::endl;
			Sleep(50);
			FOV();
		}
	case 2:
		if ((Content == 2))
		{
			system("cls");
			std::cout << "Tab number " << Content << " has been selected\nLoading it up.." << std::endl;
			Sleep(50);
			BunnyHop();
		}
	case 3:
		if ((Content == 3))
		{
			system("cls");
			std::cout << "Tab number " << Content << " has been selected\nLoading it up.." << std::endl;
			Sleep(50);
			GlowESP();
		}
	case 4:
		if ((Content == 4))
		{
			system("cls");
			std::cout << "Tab number " << Content << " has been selected\nLoading it up.." << std::endl;
			Sleep(50);
			TriggerBot();
		}
	case 5:
		if ((Content == 5))
		{
			system("cls");
			std::cout << "Tab number " << Content << " has been selected\nLoading it up.." << std::endl;
			Sleep(50);
			RadarHack();
		}
	case 6:
		if ((Content == 6))
		{
			system("cls");
			std::cout << "Tab number " << Content << " has been selected\nLoading it up.." << std::endl;
			Sleep(50);
			ThirdPerson();
		}
	case 7:
		if ((Content == 7))
		{
			system("cls");
			std::cout << "Tab number " << Content << " has been selected\nLoading it up.." << std::endl;
			Sleep(50);
			FlashHunter();
		}
	}
}