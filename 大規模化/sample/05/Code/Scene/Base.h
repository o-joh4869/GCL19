#pragma once

namespace Scene {
	class Base {
	protected:
		Base() {}
	public:
		virtual Base *update() { return nullptr; }
		virtual ~Base() = default;
	};
}