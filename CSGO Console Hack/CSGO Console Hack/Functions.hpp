#pragma once
#include "Includes.h"

const auto mem = Memory("csgo.exe");
uintptr_t Base = mem.GetModuleAddress("client.dll");

void FOV()
{

	system("cls");
	std::cout << "Choose your fov value: ";
	std::cin >> Val.FOValue;
	std::cout << "\nCurrent fov value: " << Val.FOValue;

	while (true)
	{
		uintptr_t LocalPlayer = mem.Read<uintptr_t>(Base + hazedumper::signatures::dwLocalPlayer);

		mem.Write<int>(LocalPlayer + hazedumper::netvars::m_iFOV, Val.FOValue);
	}
}

void BunnyHop()
{
	system("cls");
	std::string Answer;
	std::cout << "Wanna debug? [Y/N] - ";
	std::cin >> Answer;
	if (Answer == "Y" || "y")
	{
		Sleep(20);
		system("cls");
		std::cout << "Start debugging..." << std::endl;
		Sleep(50);
		std::cout << "client.dll -> " << "0x" << std::hex << Base << std::dec << std::endl;
		while (true)
		{
			uintptr_t LocalPlayer = mem.Read<uintptr_t>(Base + hazedumper::signatures::dwLocalPlayer);
			int Flags = mem.Read<int>(LocalPlayer + hazedumper::netvars::m_fFlags);

			if (GetAsyncKeyState(VK_SPACE) && Flags & (1 << 0))
			{
				int Fj = mem.Read<int>(hazedumper::signatures::dwForceJump);
				mem.Write<int>(Base + hazedumper::signatures::dwForceJump, 6);
				std::cout << "0x"<<std::hex<<LocalPlayer<<std::dec<<" Is jumping with a value of 5.." << std::endl;
				std::cout << "Not on ground." << std::endl;
			}
			else
			{
				mem.Write<int>(Base + hazedumper::signatures::dwForceJump, 4);
				std::cout << "0x" << std::hex << LocalPlayer << std::dec << " Is not jumping." << std::endl;
				std::cout << "On ground." << std::endl;
			}
		}
	}
	else if (Answer == "N" || "n")
	{
		std::cout << "Fucnking monkey, Enabled." << std::endl;
		while (true)
		{
			uintptr_t LocalPlayer = mem.Read<uintptr_t>(Base + hazedumper::signatures::dwLocalPlayer);
			int Flags = mem.Read<int>(LocalPlayer + hazedumper::netvars::m_fFlags);

			if (GetAsyncKeyState(VK_SPACE) && Flags & (1 << 0))
			{
				mem.Write<int>(Base + hazedumper::signatures::dwForceJump, 6);
			}
			else
			{
				mem.Write<int>(Base + hazedumper::signatures::dwForceJump, 4);
			}
		}
	}
}

void GlowESP()
{
	uintptr_t GlowObjMgr = mem.Read<uintptr_t>(Base + hazedumper::signatures::dwGlowObjectManager);
	system("cls");
	std::cout << "Select your RGBA colors, your teammates will automatically in white color." << std::endl;
	std::cout << "R = ";
	std::cin >> Col.R;
	std::cout << "G = ";
	std::cin >> Col.G;
	std::cout << "B = ";
	std::cin >> Col.B;
	std::cout << "A = ";
	std::cin >> Col.A;
	std::cout << "RGBA - " << Col.A << ", " << Col.G << " ," << Col.B << " ," << Col.A<<std::endl;
	while (true)
	{
		uintptr_t LocalPlayer = mem.Read<uintptr_t>(Base + hazedumper::signatures::dwLocalPlayer);
		int LTeam = mem.Read<int>(LocalPlayer + hazedumper::netvars::m_iTeamNum);

		for (int i = 1; i < 32; i++)
		{
			uintptr_t Ent = mem.Read<uintptr_t>(Base + hazedumper::signatures::dwEntityList + i * 0x10);
			int ETeam = mem.Read<int>(Ent + hazedumper::netvars::m_iTeamNum);
			int GlowIdx = mem.Read<int>(Ent + hazedumper::netvars::m_iGlowIndex);

			if (LocalPlayer && Ent != NULL)
			{
				if (LTeam == ETeam)
				{
					mem.Write<float>(GlowObjMgr + (GlowIdx * 0x38) + 0x8, 255);
					mem.Write<float>(GlowObjMgr + (GlowIdx * 0x38) + 0xC, 255);
					mem.Write<float>(GlowObjMgr + (GlowIdx * 0x38) + 0x10, 255);
					mem.Write<float>(GlowObjMgr + (GlowIdx * 0x38) + 0x14, 255);
				}
				else
				{
					mem.Write<float>(GlowObjMgr + (GlowIdx * 0x38) + 0x8, Col.R);
					mem.Write<float>(GlowObjMgr + (GlowIdx * 0x38) + 0xC, Col.G);
					mem.Write<float>(GlowObjMgr + (GlowIdx * 0x38) + 0x10, Col.B);
					mem.Write<float>(GlowObjMgr + (GlowIdx * 0x38) + 0x14, Col.A);
				}
				mem.Write<bool>(GlowObjMgr + (GlowIdx * 0x38) + 0x28, true);
				mem.Write<bool>(GlowObjMgr + (GlowIdx * 0x38) + 0x29, false);
			}
		}
	}
}

void TriggerBot()
{
	system("cls");
	while (true)
	{
		uintptr_t LocalPlayer = mem.Read<uintptr_t>(Base + hazedumper::signatures::dwLocalPlayer);
		int LTeam = mem.Read<int>(LocalPlayer + hazedumper::netvars::m_iTeamNum);
		int CrosshairId = mem.Read<int>(LocalPlayer + hazedumper::netvars::m_iCrosshairId);
		for (int i = 1; i < 64; i++)
		{
			uintptr_t Ent = mem.Read<uintptr_t>(Base + hazedumper::signatures::dwEntityList + (CrosshairId - 1) * 0x10);
			int ETeam = mem.Read<int>(Ent + hazedumper::netvars::m_iTeamNum);

			if (!CrosshairId || CrosshairId > 64) continue;

			if (LTeam == ETeam) continue;

			mem.Write<int>(Base + hazedumper::signatures::dwForceAttack, 6);
			std::cout << "Enemy has been detected! "<<"Entity List -> "<<"0x"<<std::hex<<Ent<<std::dec<< std::endl;
			Sleep(2);
			mem.Write<int>(Base + hazedumper::signatures::dwForceAttack, 4);
		}
	}
}

void RadarHack()
{
	system("cls");
	std::cout << "Creating public matrix float data struct for .text and ebx.." << std::endl;
	Sleep(20);
	std::cout << "EAC has been hooked!\n Now the cheat is fully undetected." << std::endl;
	while (true)
	{
		uintptr_t LocalPlayer = mem.Read<uintptr_t>(Base + hazedumper::signatures::dwLocalPlayer);
		int LTeam = mem.Read<int>(LocalPlayer + hazedumper::netvars::m_iTeamNum);
		for (int i = 1; i < 32; i++)
		{
			uintptr_t Ent = mem.Read<uintptr_t>(Base + hazedumper::signatures::dwEntityList + i * 0x10);
			int ETeam = mem.Read<int>(Ent + hazedumper::netvars::m_iTeamNum);

			if (ETeam == LTeam) continue;

			mem.Write<bool>(Ent + hazedumper::netvars::m_bSpotted, true);
		}
	}
}

void ThirdPerson()
{
	system("cls");
	std::cout << "ThirdPerson Mode has been enabled.\n[F4] to disable it." << std::endl;
	while (true)
	{
		uintptr_t LocalPlayer = mem.Read<uintptr_t>(Base + hazedumper::signatures::dwLocalPlayer);

		if (LocalPlayer != NULL)
		{
			mem.Write<bool>(LocalPlayer + hazedumper::netvars::m_iObserverMode, true);
		}

		if (GetAsyncKeyState(VK_F4))
		{
			mem.Write<bool>(LocalPlayer + hazedumper::netvars::m_iObserverMode, false);
			Content = 0;
		}
	}
}

void FlashHunter()
{
	system("cls");
	std::cout << "You are a noob, enjoy no flashed for you buddy.." << std::endl;
	while (true)
	{
		uintptr_t LocalPlayer = mem.Read<uintptr_t>(Base + hazedumper::signatures::dwLocalPlayer);

		if (LocalPlayer != NULL)
		{
			mem.Write<float>(LocalPlayer + hazedumper::netvars::m_flFlashDuration, 0.0f);
		}
	}
}