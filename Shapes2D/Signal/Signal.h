#pragma once

#include <functional>
#include <vector>

template<typename... Args>
class Signal {

public:
	typedef std::function<void(Args...)> Slot;

private:
	std::vector<Slot> slots;

public:

	void Connect(const Slot &slot) {
		slots.push_back(slot);
	}

	template<class T>
	void Connect(T* instance, void(T::*func)(Args...)) {
		Connect([=](Args...) {
			(instance->*func)(Args...);
		});
	}

	void DisconnectAll() {
		slots.clear();
	}

	void Emit(Args... args) {
		for (auto &slot : slots) {
			slot(args...);
		}
	}
};