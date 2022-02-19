// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGeometryActor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Engine.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
    SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
    Super::BeginPlay();

    InitialLocation = GetActorLocation();

    // PrintTypes();
    // PrintStringTypes();
    // PrintTransform();

    SetColor(GeometryData.Color);
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseGeometryActor::OnTimerFired, GeometryData.TimerRate, true);
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

void ABaseGeometryActor::PrintTransform()
{
    FTransform Transform = GetActorTransform();
    FVector Location = Transform.GetLocation();
    FRotator Rotation = Transform.Rotator();
    FVector Scale3D = Transform.GetScale3D();

    UE_LOG(LogBaseGeometry, Warning, TEXT("Actor transform: %s"), *Transform.ToString());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Actor location: %s"), *Location.ToString());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Actor rotation: %s"), *Rotation.ToString());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Actor scale3d: %s"), *Scale3D.ToString());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Actor human readable transform:\n%s"), *Transform.ToHumanReadableString());
}

void ABaseGeometryActor::SetLocation()
{
    FVector CurrentLocation = GetActorLocation();
    float Time = GetWorld()->GetTimeSeconds();
    CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);
    SetActorLocation(CurrentLocation);
}

void ABaseGeometryActor::HandleMovement()
{
    switch (GeometryData.MoveType)
    {
        case EMovementType::Sin:
        {
            SetLocation();
            break;
        }
        case EMovementType::Static: break;
        default: break;
    }
}

void ABaseGeometryActor::SetColor(const FLinearColor& Color)
{
    UMaterialInstanceDynamic* DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
    if (DynMaterial)
    {
        DynMaterial->SetVectorParameterValue("Color", Color);
    }
}

void ABaseGeometryActor::OnTimerFired() {
    if (TimerCount++ < TimerMax)
    {
        const FLinearColor NewColor = FLinearColor::MakeRandomColor();
        UE_LOG(LogBaseGeometry, Warning, TEXT("Change to %s color"), *NewColor.ToString());
        SetColor(NewColor);
    }
    else
    {
        UE_LOG(LogBaseGeometry, Warning, TEXT("Timer has been stopped after %d ticks!"), TimerCount - 1);
        GetWorldTimerManager().ClearTimer(TimerHandle);
    }
}
