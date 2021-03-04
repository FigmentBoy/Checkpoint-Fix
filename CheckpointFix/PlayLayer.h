#pragma once
#include <Windows.h>
#include <vector>
#include "CheckPoint.h"
#include "Minhook/MinHook.h"

namespace PlayLayer {
	inline bool(__thiscall* init)(void* self, void* GJGameLevel);
	bool __fastcall initHook(void* self, void*, void* GJGameLevel);

	inline void(__thiscall* togglePractice)(void* self, bool practice);
	void __fastcall hkTogglePractice(void* self, int edx, bool practice);

	inline int(__thiscall* createCheckpoint)(void* self);
	int __fastcall hkCreateCheckpoint(void* self);

	inline int(__thiscall* removeCheckpoint)(void* self);
	int __fastcall hkRemoveCheckpoint(void* self);

	inline int(__thiscall* resetLevel)(void* self);
	int __fastcall hkResetLevel(void* self);

	inline bool(__thiscall* levelComplete)(void* self);
	bool __fastcall hkLevelComplete(void* self);

	inline void(__thiscall* exit)(void* self);
	void __fastcall hkExit(void* self);

	void mem_init();

	extern std::vector<CheckPoint> checkpoints;
	extern bool inPractice;
}