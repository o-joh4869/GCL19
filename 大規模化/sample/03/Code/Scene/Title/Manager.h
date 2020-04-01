#pragma once
#include"../Base.h"

namespace Scene { namespace Title {
	class Manager : public Scene::Base {
	public:
		Manager();
		virtual void update() override;
		virtual ~Manager() = default;
	};
}}