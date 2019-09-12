#pragma once

class Script
{
public:
	Script();
	~Script() = default;

	void Init();

	const bool LoadFromFile(const std::string& path, class AAA* aaa);
	const bool ExcuteFunc();

private:
	asIScriptEngine* scriptEngine;
	CScriptBuilder* scriptBuilder;
	
	std::string path;
	std::string className;

	asIScriptObject* scriptOBJ;
	asIScriptFunction* excuteFUNC;
	asIScriptFunction* constructorFUNC;

private:
	static int moduleNum;
};