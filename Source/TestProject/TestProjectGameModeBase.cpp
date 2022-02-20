// Copyright Epic Games, Inc. All Rights Reserved.

#include "SandboxPawn.h"
#include "SandboxPlayerController.h"
#include "TestProjectGameModeBase.h"

ATestProjectGameModeBase::ATestProjectGameModeBase()
{
    DefaultPawnClass = ASandboxPawn::StaticClass();
    PlayerControllerClass = ASandboxPlayerController::StaticClass();
}