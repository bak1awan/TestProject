// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"

UENUM(BlueprintType)
enum class EMovementType : uint8
{
    Sin,
    Static
};

USTRUCT(BlueprintType)
struct FGeometryData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, Category = "Movement")
    float Amplitude = 50.0f;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float Frequency = 2.0f;

    UPROPERTY(EditAnywhere, Category = "Movement")
    EMovementType MoveType = EMovementType::Static;

    UPROPERTY(EditAnywhere, Category = "Design")
    FLinearColor Color = FLinearColor::Black;

    UPROPERTY(EditAnywhere, Category = "Design")
    float TimerRate = 1.f;
};

UCLASS()
class TESTPROJECT_API ABaseGeometryActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABaseGeometryActor();

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* BaseMesh;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "GeometryData")
    FGeometryData GeometryData;

    UPROPERTY(EditAnywhere, Category = "Weapon")
    int WeaponsNum = 4;

    UPROPERTY(EditAnywhere, Category = "Stat")
    int KillsNum = 7;

    UPROPERTY(EditAnywhere, Category = "Health")
    float Health = 34.435f;

    UPROPERTY(EditAnywhere, Category = "Health")
    bool bIsDead = false;

    UPROPERTY(EditAnywhere, Category = "Weapon")
    bool bHasWeapon = true;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    FVector InitialLocation;
    FTimerHandle TimerHandle;
    int32 TimerCount = 0;
    int32 TimerMax = 5;

    void PrintTypes();
    void PrintStringTypes();
    void PrintTransform();
    void SetLocation();
    void HandleMovement();
    void SetColor(const FLinearColor&);
    void OnTimerFired();
};
