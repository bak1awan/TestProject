// Copyright Epic Games, Inc. All Rights Reserved.

#include "SandboxPawn.h"
#include "TestProjectGameModeBase.h"

ATestProjectGameModeBase::ATestProjectGameModeBase()
{
    DefaultPawnClass = ASandboxPawn::StaticClass();
}