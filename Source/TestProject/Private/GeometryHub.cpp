// Fill out your copyright notice in the Description page of Project Settings.

#include "GeometryHub.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryHub, All, All)

// Sets default values
AGeometryHub::AGeometryHub()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

void AGeometryHub::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
    UE_LOG(LogGeometryHub, Warning, TEXT("Color %s changed on %s."), *Color.ToString(), *Name);
}

void AGeometryHub::OnTimerFinished(AActor* Actor)
{
    ABaseGeometryActor* NewActor = Cast<ABaseGeometryActor>(Actor);
    if (!NewActor) return;
    UE_LOG(LogGeometryHub, Warning, TEXT("Down-cast worked! The amplitude is %.2f!"), NewActor->GetGeometryData().Amplitude);
    UE_LOG(LogGeometryHub, Error, TEXT("Time finished on %s!"), *Actor->GetName());
    UE_LOG(LogGeometryHub, Error, TEXT("\n%s"), *NewActor->GetGeometryData().ToString());
    NewActor->Destroy();
}

// Called when the game starts or when spawned
void AGeometryHub::BeginPlay()
{
    Super::BeginPlay();
    SpawnDeeply();
    // SpawnDeferred();
    // SpawnInstantly();
}
// Called every frame
void AGeometryHub::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AGeometryHub::SpawnInstantly()
{
    UWorld* World = GetWorld();
    if (World)
    {
        for (int32 i = 0; i < 10; ++i)
        {
            const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 0.0f));
            ABaseGeometryActor* Geometry = World->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);

            if (Geometry)
            {
                FGeometryData Data;
                Data.MoveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
                Geometry->SetGeometryData(Data);
            }
        }
    }
}

void AGeometryHub::SpawnDeferred()
{
    UWorld* World = GetWorld();
    if (World)
    {
        for (int32 i = 0; i < 10; ++i)
        {
            const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 300.0f));
            ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryTransform);

            if (Geometry)
            {
                FGeometryData Data;
                Data.Color = FLinearColor::MakeRandomColor();
                Geometry->SetGeometryData(Data);
                Geometry->FinishSpawning(GeometryTransform);
            }
        }
    }
}

void AGeometryHub::SpawnDeeply()
{
    UWorld* World = GetWorld();
    if (World)
    {
        for (const auto& Payload : GeometryPayloads)
        {
            ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(Payload.GeometryClass, Payload.InitialTransform);

            if (Geometry)
            {
                Geometry->SetGeometryData(Payload.Data);
                Geometry->OnColorChanged.AddDynamic(this, &AGeometryHub::OnColorChanged);
                Geometry->OnTimerFinished.AddUObject(this, &AGeometryHub::OnTimerFinished);
                Geometry->FinishSpawning(Payload.InitialTransform);
            }
        }
    }
}
