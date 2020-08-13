// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DrawDebugHelpers.h"
#include "GunProjectileActor.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunActor.generated.h"

UCLASS()
class BATTLEGROUND_API AGunActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunActor();

	virtual void Tick(float DeltaTime) override;

	void SetupGunDirection();
	
	void SpawnProjectile();
	void PullTrigger();
	void SetMaxBulletsCount(int32);
	void SetMaxCountBulletsInMagazine(int32);

	float GetAutoFireRate();

	int32 GetMaxBulletsCount();
	int32 GetMaxCountBulletsInMagazine();

	FVector2D  GetScreenLocation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere)
		UParticleSystem* MuzzleFlash = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float AutoFireRate = 0.2f;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float BulletMaxRange = 60000.f; // 600 meter

	UPROPERTY(EditAnywhere, Category = "Setup")
		int32 MaxBulletsCount = 360; // 600 meter

	UPROPERTY(EditAnywhere, Category = "Setup")
		int32 MaxCountBulletsInMagazine = 36; // 600 meter

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AGunProjectileActor> GunProjectileActorClass;

	AGunProjectileActor* GunProjectileActor = nullptr;

	FVector2D OUT ScreenLocation;
};
