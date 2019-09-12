#pragma once

class ScriptManager
{
public:
	static ScriptManager* Get()
	{ 
		static ScriptManager instance;
		return &instance; 
	}

	void Initialize();

	class asIScriptContext* RequestContext();
	void ReturnContext(asIScriptContext* ctx);

	class asIScriptEngine* GetScriptEngine() { return scriptEngine; }

private:
	ScriptManager();
	~ScriptManager();

	void RegisterFunction();
	void MessageCallback(const struct asSMessageInfo* msg);


private:
	class asIScriptEngine* scriptEngine;
	std::stack<class asIScriptContext*> ctxs;
};