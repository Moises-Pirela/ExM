#pragma once

enum ELogLevel {
	LOG_INFO,
	LOG_DEBUG,
	LOG_WARNING,
	LOG_ERROR,
	LOG_MAX,
};

inline FColor logColorLookUp[LOG_MAX]
{
	FColor::White,
	FColor::Green,
	FColor::Yellow,
	FColor::Red
};


static void NecroLog(FString& message, ELogLevel level = LOG_INFO, bool bOnScreen = true)
{
	switch(level)
	{
	case LOG_WARNING:
		UE_LOG(LogTemp, Warning, TEXT("%s"), *message);
		break;

	case LOG_ERROR:
		UE_LOG(LogTemp, Error, TEXT("%s"), *message);
		break;

	case LOG_INFO:
	default:
		UE_LOG(LogTemp, Log, TEXT("%s"), *message);
		break;
	}

	if(bOnScreen)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.0f,
			logColorLookUp[level],
			message
		);
	}
}