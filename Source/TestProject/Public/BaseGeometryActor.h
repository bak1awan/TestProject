// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanged, const FLinearColor&, Color, const FString&, Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);

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

    FString ToString();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float Amplitude = 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float Frequency = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    EMovementType MoveType = EMovementType::Static;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
    FLinearColor Color = FLinearColor::Black;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
    float TimerRate = 2.f;
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

    UPROPERTY(BlueprintAssignable)
    FOnColorChanged OnColorChanged;

    FOnTimerFinished OnTimerFinished;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeometryData")
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

    UFUNCTION(BlueprintCallable)
    FGeometryData GetGeometryData() { return GeometryData; }

    void SetGeometryData(const FGeometryData& Data) { GeometryData = Data; };

private:
    FVector InitialLocation;
    FTimerHandle TimerHandle;
    int32 TimerCount = 0;
    int32 TimerMax = 5;

    void PrintTypes();
    void PrintStringTypes();
    void PrintTransform();
    void HandleMovement();
    void SetColor(const FLinearColor&);
    void OnTimerFired();
};
