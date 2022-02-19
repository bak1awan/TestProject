// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGeometryActor.h"
#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

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
    // PrintStringTypes();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABaseGeometryActor::PrintTypes()
{
    UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name: %s"), *GetName());
    UE_LOG(LogBaseGeometry, Warning, TEXT("WeaponsNum: %d"), WeaponsNum);
    UE_LOG(LogBaseGeometry, Warning, TEXT("KillsNum: %d"), KillsNum);
    UE_LOG(LogBaseGeometry, Warning, TEXT("Health: %.2f"), Health);
    UE_LOG(LogBaseGeometry, Warning, TEXT("IsDead: %d"), bIsDead);
    UE_LOG(LogBaseGeometry, Warning, TEXT("HasWeapon: %d"), bHasWeapon);
}

void ABaseGeometryActor::PrintStringTypes()
{
    FString Name = "John Connor";
    UE_LOG(LogBaseGeometry, Warning, TEXT("Name: %s"), *Name);

    FString WeaponsNumString = "WeaponsNum: " + FString::FromInt(WeaponsNum) + "\n";
    FString KillsNumString = "KillsNum: " + FString::FromInt(WeaponsNum) + "\n";
    FString HealthString = "Health: " + FString::SanitizeFloat(Health) + "\n";
    FString IsDeadString = "IsDead: " + FString(bIsDead ? "true" : "false") + "\n";
    FString HasWeaponString = "HasWeapo: " + FString(bHasWeapon ? "true" : "false") + "\n";

    FString Statistics = FString::Printf(
        TEXT("\n=== All Statistics ===\n%s%s%s%s%s"), *WeaponsNumString, *KillsNumString, *HealthString, *IsDeadString, *HasWeaponString);

    UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *Statistics);

    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Name);
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Statistics, true, FVector2D(1.5f, 1.5f));
}