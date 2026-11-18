#pragma once
#include "Scene.h"

class Instance1 : public Scene
{
public:
	void init() override;
	void updata(float dt) override;
};

class Instance2 : public Scene
{
public:
	void init() override;
	void updata(float dt) override;
};

class Instance3 : public Scene
{
public:
	void init() override;
	void updata(float dt) override;
};
