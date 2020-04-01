#pragma once

class SceneBase {
protected:
	SceneBase() {}
public:
	virtual void update() {}
	virtual ~SceneBase() = default;
};