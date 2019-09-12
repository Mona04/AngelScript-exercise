#pragma once

class ScriptManager
{
public:
	ScriptManager();
	~ScriptManager();

	void Initialize();

	asIScriptEngine* GetScriptEngine() { return scriptEngine; }

private:
	class asIScriptEngine* scriptEngine;
	std::vector<class asIScriptContext*> ctxs;
};