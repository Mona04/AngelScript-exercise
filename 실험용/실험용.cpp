#include "pch.h"

void main()
{
	AAA* aaa = new AAA();
	ScriptManager::Get()->Initialize();
	Script* script = new Script();
	script->Init();
	script->LoadFromFile("../script/BBB.as", aaa);
	script->ExcuteFunc();

	while (1);
}