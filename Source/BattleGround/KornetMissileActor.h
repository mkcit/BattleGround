
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once		
#include "GameFramework/RotatingMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework\SpringArmComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KornetMissileActor.generated.h"

UCLASS()
class BATTLEGROUND_API AKornetMissileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKornetMissileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ActivateMissileRotation();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UCameraComponent* GetCamera();

	void GuidMissile(FVector Target);

private:
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* Missile = nullptr;

	UPROPERTY(VisibleDefaultsOnly)
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(VisibleDefaultsOnly)
	UCameraComponent* Camera = nullptr;


	UPROPERTY(EditAnywhere, Category = "Setup")
	float RotationSpeedRate = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MovementSpeedRate = 2500.f;

	UPROPERTY(EditAnywhere)
	float MaxRotationAngleRange = 25.f;


	UPROPERTY(EditAnywhere)
	UParticleSystem* MissileCollisionEmitter = nullptr;

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(EditAnywhere)
	URadialForceComponent* RadialForceComponent = nullptr;

	UPROPERTY(EditAnywhere)
	URotatingMovementComponent* RotatingMovementComponent = nullptr;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
