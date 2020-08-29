// Fill out your copyright notice in the Description page of Project Settings.

#include "TimerManager.h"
#include "KornetSystemActor.h"

// Sets default values
AKornetSystemActor::AKornetSystemActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Legs = CreateDefaultSubobject<UStaticMeshComponent>(FName("Legs")); 
	RightLeftScene = CreateDefaultSubobject<USceneComponent>(FName("RightLeftScene"));
	UpDownScene = CreateDefaultSubobject<USceneComponent>(FName("UpDownScene"));
	VisionSystem = CreateDefaultSubobject<UStaticMeshComponent>(FName("VisionSystem"));
	Container = CreateDefaultSubobject<UStaticMeshComponent>(FName("Container"));
	FrontCover = CreateDefaultSubobject<UStaticMeshComponent>(FName("FrontCover"));
	BackCover = CreateDefaultSubobject<UStaticMeshComponent>(FName("BackCover"));
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));

	SetRootComponent(Legs);
	RightLeftScene->SetupAttachment(Legs); 
	UpDownScene->SetupAttachment(RightLeftScene);
	VisionSystem->SetupAttachment(UpDownScene);
	Container->SetupAttachment(VisionSystem);
	Camera->SetupAttachment(VisionSystem);
	FrontCover->SetupAttachment(Container);
	BackCover->SetupAttachment(Container);
}

// Called when the game starts or when spawned
void AKornetSystemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKornetSystemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKornetSystemActor::Fire()
{
	if (Container)
	{
		OpenContainerCovers();

		FTimerHandle Timer;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &AKornetSystemActor::FireMissile, 0.5f, false);
	}
	
}

void AKornetSystemActor::FireMissile()
{
	FTransform MissileSocketTransofrmation = Container->GetSocketTransform(FName("Missile Socket"));

	KorneMissileActor = GetWorld()->SpawnActor<AKornetMissileActor>(KornetMissileActorClass, MissileSocketTransofrmation);
}

void AKornetSystemActor::OpenContainerCovers()
{
	if (!FrontCover || !BackCover) return;

	FrontCover->SetSimulatePhysics(true);
	BackCover->SetSimulatePhysics(true);

	FVector Impulse = FrontCover->GetForwardVector() * 1200;

	FrontCover->AddImpulse(Impulse);
	BackCover->AddImpulse(Impulse * (-1));
}

USceneComponent* AKornetSystemActor::GetRightLeftScene()
{
	return RightLeftScene;
}

USceneComponent* AKornetSystemActor::GetUpDownScene()
{
	return UpDownScene;
}

UStaticMeshComponent* AKornetSystemActor::GetVisionSystem()
{
	return VisionSystem;
}

AKornetMissileActor* AKornetSystemActor::GetLastFiredMissile()
{
	return KorneMissileActor;
}

void AKornetSystemActor::ActiveNavigatorSystem()
{
	
	if (!VisionSystem || !KorneMissileActor) return;

	if (KorneMissileActor->IsActorBeingDestroyed()) return;

	FVector LineStart = VisionSystem->GetComponentLocation();
	FVector Direction = VisionSystem->GetForwardVector();
	FVector LineEnd = LineStart + Direction * MissileRange;

	FHitResult Hit;
	bool Success = GetWorld()->LineTraceSingleByChannel(Hit, LineStart, LineEnd, ECollisionChannel::ECC_Visibility);
	
	if (Success)
	{
		if (KorneMissileActor && Hit.GetActor() != KorneMissileActor)
			KorneMissileActor->GuidMissile(Hit.Location);
	}
}

