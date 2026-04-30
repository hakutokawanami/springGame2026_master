#pragma once
#include<EffekseerForDXLib.h>
#include"../system/Vector3.h"
#include<string>
class EffectManager
{
public:
	EffectManager();						
	~EffectManager();						
	static void Init();	
	static void End();
	static void Load(const std::string& name,const std::string& path);						
	static int Play(const std::string& name, Vector3 pos, float yaw);

	static void Update();
	static void Draw();

	static void StopAll();
private:
	static std::map<std::string, int>m_effects;
};

