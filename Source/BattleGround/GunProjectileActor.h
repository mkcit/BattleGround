// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/ProjectileMovementComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunProjectileActor.generated.h"

UCLASS()
class BATTLEGROUND_API AGunProjectileActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGunProjectileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UProjectileMovementComponent* GetProjectileMovement();


private:
	UPROPERTY(EditAnywhere)
	USceneComponent* Root = nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Projectile = nullptr;

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
