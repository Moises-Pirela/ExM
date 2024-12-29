#pragma once

enum ELogLevel {
	LOG_INFO,
	LOG_DEBUG,
	LOG_ERROR,
	LOG_MAX,
};

inline FColor logColorLookUp[LOG_MAX]
{
	FColor::Green,
	FColor::Yellow,
	FColor::Red
};


static void NecroLog(FString& message, ELogLevel level = LOG_INFO) {
	GEngine->AddOnScreenDebugMessage(
				-1,
				5.0f,
				logColorLookUp[level],
				message
			);
}