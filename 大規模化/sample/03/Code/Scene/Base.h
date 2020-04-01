#pragma once

namespace Scene {
	class Base {
	protected:
		Base() {}
	public:
		virtual void update() {}
		virtual ~Base() = default;
	};
}