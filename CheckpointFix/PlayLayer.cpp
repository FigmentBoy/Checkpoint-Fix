#include "PlayLayer.h"

namespace PlayLayer {
	std::vector<CheckPoint> checkpoints;
	bool inPractice = false;

	bool __fastcall initHook(void* self, void*, void* GJGameLevel) {
		checkpoints.clear();
		inPractice = false;
		return init(self, GJGameLevel);
	}

	void __fastcall hkTogglePractice(void* self, int edx, bool practice) {
		checkpoints.clear();
		inPractice = practice;
		return togglePractice(self, practice);
	}

	int __fastcall hkCreateCheckpoint(void* self) {
		if (*(void**)((char*)self + 0x224) != nullptr) {
			checkpoints.push_back({
				CheckPoint::from(self)
			});
		}
		return createCheckpoint(self);
	}

	int __fastcall hkRemoveCheckpoint(void* self) {
		if (checkpoints.size() > 0) {
			checkpoints.pop_back();
		}

		return PlayLayer::removeCheckpoint(self);
	}

	int __fastcall hkResetLevel(void* self) {
		int result = resetLevel(self);

		if (inPractice && checkpoints.size() > 0) {
			checkpoints.back().restore(self);
		}

		return result;
	}

	bool __fastcall hkLevelComplete(void* self) {
		checkpoints.clear();
		inPractice = false;
		return levelComplete(self);
	};

	void __fastcall hkExit(void* self) {
		checkpoints.clear();
		return exit(self);
	}

	void mem_init() {
		size_t base = (size_t)GetModuleHandle(0);

		MH_CreateHook(
			(PVOID)(base + 0x01FB780),
			PlayLayer::initHook,
			(LPVOID*)&PlayLayer::init);

		MH_CreateHook(
			(PVOID)(base + 0x20D0D0),
			PlayLayer::hkTogglePractice,
			(LPVOID*)&PlayLayer::togglePractice);

		MH_CreateHook(
			(PVOID)(base + 0x20B050),
			PlayLayer::hkCreateCheckpoint,
			(LPVOID*)&PlayLayer::createCheckpoint);

		MH_CreateHook(
			(PVOID)(base + 0x20B830),
			PlayLayer::hkRemoveCheckpoint,
			(LPVOID*)&PlayLayer::removeCheckpoint);

		MH_CreateHook(
			(PVOID)(base + 0x20BF00),
			PlayLayer::hkResetLevel,
			(LPVOID*)&PlayLayer::resetLevel);

		MH_CreateHook(
			(PVOID)(base + 0x1FD3D0),
			PlayLayer::hkLevelComplete,
			(LPVOID*)&PlayLayer::levelComplete);

		MH_CreateHook(
			(PVOID)(base + 0x020D810),
			PlayLayer::hkExit,
			(LPVOID*)&PlayLayer::exit);
	}
}