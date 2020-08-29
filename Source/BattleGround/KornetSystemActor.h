// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DrawDebugHelpers.h"
#include "KornetMissileActor.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KornetSystemActor.generated.h"

UCLASS()
class BATTLEGROUND_API AKornetSystemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKornetSystemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire();

	void FireMissile();

	void OpenContainerCovers();

	UStaticMeshComponent* GetVisionSystem(); 
	USceneComponent* GetRightLeftScene();
	USceneComponent* GetUpDownScene();
	AKornetMissileActor* GetLastFiredMissile();

	void ActiveNavigatorSystem();

private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Legs = nullptr;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RightLeftScene = nullptr;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* UpDownScene = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisionSystem = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Container = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FrontCover = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BackCover = nullptr;

	UPROPERTY(VisibleDefaultsOnly)
	UCameraComponent* Camera = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AKornetMissileActor> KornetMissileActorClass;

	UPROPERTY(EditAnywhere)
	float MissileRange = 400000.f;


	AKornetMissileActor* KorneMissileActor = nullptr;

};
