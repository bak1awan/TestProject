// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SandboxPawn.h"
#include "SandboxPlayerController.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPlayerController, All, All)

void ASandboxPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAction("ChangePawn", IE_Pressed, this, &ASandboxPlayerController::ChangePawn);
}

void ASandboxPlayerController::BeginPlay() {
    Super::BeginPlay();
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandboxPawn::StaticClass(), Pawns);
}

void ASandboxPlayerController::ChangePawn()
{
    if (Pawns.Num() <= 1) return;
    ASandboxPawn* CurrentPawn = Cast<ASandboxPawn>(Pawns[CurrentPawnIndex]);
    if (!CurrentPawn) return;
    CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();
    UE_LOG(LogSandboxPlayerController, Error, TEXT("The Pawn has benn changed!"));
    Possess(CurrentPawn);
}
