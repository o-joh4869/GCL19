#pragma once
#include"SceneBase.h"

class Title : public SceneBase {
public:
	Title();
	virtual void update() override;
	virtual ~Title() = default;
};