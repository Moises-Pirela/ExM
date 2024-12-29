#pragma once

class ENTITYCONFIGEDITOR_API EntityConfigEditorModule : public IModuleInterface {
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};