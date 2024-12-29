#include "EntityConfigCustomization.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "PropertyHandle.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "ExM/ExMCore/Configs/EntityConfig.h"

TSharedRef<IDetailCustomization> UEntityConfigCustomization::MakeInstance()
{
    return MakeShareable(new UEntityConfigCustomization);
}

void UEntityConfigCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
    IDetailCategoryBuilder& ComponentsCategory = DetailBuilder.EditCategory("Components");

    TSharedRef<IPropertyHandle> ComponentConfigsHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UEntityConfig, componentConfigs));
    if (!ComponentConfigsHandle->IsValidHandle())
    {
        UE_LOG(LogTemp, Error, TEXT("ComponentConfigsHandle is invalid"));
        return;
    }

    ComponentsCategory.AddProperty(ComponentConfigsHandle);

    ComponentsCategory.AddCustomRow(FText::FromString("Add Component"))
        .WholeRowContent()
        [
            SNew(SButton)
            .Text(FText::FromString("Add Component"))
            .OnClicked(FOnClicked::CreateLambda([ComponentConfigsHandle]() -> FReply
            {
                TArray<UObject*> OuterObjects;
                ComponentConfigsHandle->GetOuterObjects(OuterObjects);

                if (OuterObjects.Num() > 0)
                {
                    if (UEntityConfig* EntityConfig = Cast<UEntityConfig>(OuterObjects[0]))
                    {
                        UEntityComponentConfigBase* NewComponentConfig = NewObject<UEntityComponentConfigBase>(EntityConfig, UEntityComponentConfigBase::StaticClass());

                        if (NewComponentConfig)
                        {
                            EntityConfig->componentConfigs.Add(NewComponentConfig);

                            EntityConfig->Modify();

                            ComponentConfigsHandle->NotifyPostChange(EPropertyChangeType::ArrayAdd);
                        }
                    }
                }

                return FReply::Handled();
            }))
        ];

    DetailBuilder.ForceRefreshDetails();
}
