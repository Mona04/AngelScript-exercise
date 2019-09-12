#include "pch.h"
#include "ScriptManager.h"

ScriptManager::ScriptManager()
{
}

ScriptManager::~ScriptManager()
{
	while (!ctxs.empty())
	{
		ctxs.top()->Release();
		ctxs.pop();
	}

	if (scriptEngine)
	{
		scriptEngine->ShutDownAndRelease();
		scriptEngine = nullptr;
	}
}

void ScriptManager::Initialize()
{
	scriptEngine = asCreateScriptEngine(ANGELSCRIPT_VERSION);

	RegisterStdString(scriptEngine);   // std::string 클래스 넣기
	RegisterFunction();

	scriptEngine->SetMessageCallback(asMETHOD(ScriptManager, MessageCallback), this, asCALL_THISCALL);
	//scriptEngine->SetEngineProperty(asEP_BUILD_WITHOUT_LINE_CUES, true);
}

void ScriptManager::RegisterFunction()
{
	int r;

	r = scriptEngine->RegisterObjectType("AAA", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("AAA", "AAA &opAssign(const AAA &in)", asMETHODPR(AAA, operator =, (const AAA&), AAA&), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("AAA", "void Excute()", asMETHOD(AAA, Excute), asCALL_THISCALL); assert(r >= 0);
}

void ScriptManager::MessageCallback(const asSMessageInfo* msg)
{
	char buffer[1024];

	const char* type = "ERR ";
	if (msg->type == asMSGTYPE_WARNING)
		type = "WARN";
	else if (msg->type == asMSGTYPE_INFORMATION)
		type = "INFO";

	sprintf_s(buffer,"%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
	
	MessageBoxA(nullptr, buffer, nullptr, MB_OK);
}

asIScriptContext* ScriptManager::RequestContext()
{
	if (ctxs.empty())
		return scriptEngine->CreateContext();
	else
	{
		asIScriptContext* ctx = ctxs.top();
		ctxs.pop();

		return ctx;
	}
}

void ScriptManager::ReturnContext(asIScriptContext* ctx)
{
	ctxs.emplace(ctx);
}
