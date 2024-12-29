
#include "EntityConfigEditor.h"

#include "EntityConfigCustomization.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FDefaultModuleImpl, EntityConfigEditor);

void EntityConfigEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyEditorModule.RegisterCustomClassLayout(
		"EntityConfig",
		FOnGetDetailCustomizationInstance::CreateStatic(&UEntityConfigCustomization::MakeInstance)
	);

	PropertyEditorModule.NotifyCustomizationModuleChanged();
}

void EntityConfigEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyEditorModule.UnregisterCustomClassLayout("EntityConfig");
	}
}
