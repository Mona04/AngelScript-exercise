#include "pch.h"
#include "Script.h"

int Script::moduleNum = 0;

Script::Script()
	: scriptEngine(nullptr)
	, scriptBuilder(nullptr)
	, path("")
	, className("")
	, scriptOBJ(nullptr)
	, excuteFUNC(nullptr)
	, constructorFUNC(nullptr)
{
}

void Script::Init()
{
	scriptEngine = ScriptManager::Get()->GetScriptEngine();
	scriptBuilder = new CScriptBuilder();
}

const bool Script::LoadFromFile(const std::string& path, class AAA* aaa)
{
	this->path = path;
	this->className = FileSystem::GetIntactFileNameFromPath(path);

	int r;

	//BuilderSet
	r = scriptBuilder->StartNewModule(scriptEngine, (className + std::to_string(moduleNum++)).c_str()); assert(r >= 0);
	r = scriptBuilder->AddSectionFromFile(path.c_str()); assert(r >= 0);
	r = scriptBuilder->BuildModule(); assert(r >= 0);
	
	//Get functions in the script
	int typeID = scriptBuilder->GetModule()->GetTypeIdByDecl(className.c_str()); assert(typeID);
	asITypeInfo* type = scriptEngine->GetTypeInfoById(typeID); assert(type);
	excuteFUNC = type->GetMethodByDecl("void Excute()"); assert(excuteFUNC);
	asIScriptFunction* constructorFUNC = type->GetFactoryByDecl((className + " @" + className + "(AAA @)").c_str()); assert(constructorFUNC);

	asIScriptContext* ctx = scriptEngine->RequestContext();
	{
		int r;
		r = ctx->Prepare(constructorFUNC); assert(r == 0);
		r = ctx->SetArgObject(0, aaa); assert(r == 0);
		r = ctx->Execute(); assert(r == 0);

		scriptOBJ = *static_cast<asIScriptObject**>(ctx->GetAddressOfReturnValue());
		scriptOBJ->AddRef();

		r = ctx->Unprepare(); assert(r >= 0);
	}
	scriptEngine->ReturnContext(ctx);

	return true;
}

const bool Script::ExcuteFunc()
{
	asIScriptContext* ctx = ScriptManager::Get()->RequestContext();
	{
		int r;
		r = ctx->Prepare(excuteFUNC); assert(r == 0);
		r = ctx->SetObject(scriptOBJ); assert(r == 0);
		r = ctx->Execute(); assert(r == 0);
		r = ctx->Unprepare(); assert(r == 0);
	}
	ScriptManager::Get()->ReturnContext(ctx);

	return true;
}

