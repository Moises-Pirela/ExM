// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.


#include "ExmGameInstance.h"
#include "ExM/ExMCore/Configs/EntityConfig.h"
#include "ExM/ExMCore/Configs/BuffDataTableRow.h"

UExmGameInstance::UExmGameInstance()
{
}

void UExmGameInstance::Init()
{
	Super::Init();

	if (auto dataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/_/Configs/DT_BuffDataTable")))
	{
		TArray<FBuffDataTableRow*> BuffRows;
		dataTable->GetAllRows(TEXT(""), BuffRows);

		int configId = 0;
		
		for (FBuffDataTableRow* BuffRow : BuffRows)
		{
			BuffRow->id = configId;
			BuffDataArray.Add(*BuffRow);
			configId++;
		}
	}
}
