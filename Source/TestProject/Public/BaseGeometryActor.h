// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"

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
    UPROPERTY(EditAnywhere, Category = "Movement")
    float Amplitude = 50.f;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float Frequency = 2.f;

    FVector InitialLocation;

    void PrintTypes();
    void PrintStringTypes();
    void PrintTransform();
};
