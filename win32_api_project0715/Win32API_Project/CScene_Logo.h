#pragma once
#include "CScene.h"
class CScene_Logo :
    public CScene
{
public:
    virtual void SceneInit() override;
    virtual void SceneTick() override;

public:
    CScene_Logo();
    ~CScene_Logo();
};

