// Fill out your copyright notice in the Description page of Project Settings.


// TerminalManager.cpp
#include "TerminalManager.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include <iostream> //For the std::cout

ATerminalManager::ATerminalManager()
{
	// Add Command mappings here
	CommandMap["move north"] = [this]() { MovePlayer("north"); };
	CommandMap["move south"] = [this]() { MovePlayer("south"); };
	CommandMap["move east"] = [this]() { MovePlayer("east"); };
	CommandMap["move west"] = [this]() { MovePlayer("west"); };
	CommandMap["inspect figure"] = [this]() { InspectFigure(); };
	CommandMap["set game volume"] = [this]() { ChangeSettings("volume", ""); };
}

void ATerminalManager::HandleCommand(const FString& Command)
{
	ParseCommand(Command);
}

void ATerminalManager::ParseCommand(const FString& Command)
{
	FString LowerCaseCommand = Command.ToLower(); // To handle different cases.
	bool found = false;

	for (auto const& [key, val] : CommandMap)
	{
		if (LowerCaseCommand.StartsWith(key))
		{
			ExecuteCommand(key);
			found = true;
			break;
		}
	}
	if (!found)
	{
		OnOutputReceived.Broadcast("Unknown Command");
	}

}

void ATerminalManager::ExecuteCommand(const FString& ParsedCommand)
{
	if (CommandMap.count(ParsedCommand) > 0)
	{
		CommandMap[ParsedCommand]();
	}
}

void ATerminalManager::MovePlayer(const FString& Direction)
{
	if (auto* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		FString OutputMessage = FString::Printf(TEXT("Moving player %s"), *Direction);
		OnOutputReceived.Broadcast(OutputMessage);

		//Move player actor here.
	}
}

void ATerminalManager::InspectFigure()
{
	OnOutputReceived.Broadcast("Inspecting figure...");
	// Implement your inspect functionality here
}

void ATerminalManager::ChangeSettings(const FString& setting, const FString& value)
{
	if (setting == "volume")
	{
		OnOutputReceived.Broadcast("Changing game volume...");
		//Implement change settings here.
	}
}