// Fill out your copyright notice in the Description page of Project Settings.

// TerminalManager.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TerminalManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTextOutputDelegate, FString, OutputText);

UCLASS()
class CORPSETERMINAL_API ATerminalManager : public AActor
{
	GENERATED_BODY()

public:
	ATerminalManager();

	UFUNCTION(BlueprintCallable, Category = "Terminal")
	void HandleCommand(const FString& Command);

	UPROPERTY(BlueprintAssignable, Category = "Terminal")
	FTextOutputDelegate OnOutputReceived;

private:
	void ParseCommand(const FString& Command);
	void ExecuteCommand(const FString& ParsedCommand);
	void MovePlayer(const FString& Direction);
	void InspectFigure();
	void ChangeSettings(const FString& setting, const FString& value);
	// command mappings
	std::map<FString, std::function<void()>> CommandMap;
};