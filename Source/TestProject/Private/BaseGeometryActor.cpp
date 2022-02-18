// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGeometryActor.h"

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
    Super::BeginPlay();

    PrintTypes();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABaseGeometryActor::PrintTypes()
{
    UE_LOG(LogTemp, Display, TEXT("Hello, Display!"));
    UE_LOG(LogTemp, Warning, TEXT("Hello, Warning!"));
    UE_LOG(LogTemp, Error, TEXT("Hello, Error!"));

    int WeaponsNum = 4;
    int KillsNum = 7;
    float Health = 34.435f;
    bool bIsDead = false;
    bool bHasWeapon = true;

    UE_LOG(LogTemp, Display, TEXT("WeaponsNum: %d"), WeaponsNum);
    UE_LOG(LogTemp, Display, TEXT("KillsNum: %d"), KillsNum);
    UE_LOG(LogTemp, Display, TEXT("Health: %.2f"), Health);
    UE_LOG(LogTemp, Display, TEXT("IsDead: %d"), bIsDead);
    UE_LOG(LogTemp, Display, TEXT("HasWeapon: %d"), bHasWeapon);
}
