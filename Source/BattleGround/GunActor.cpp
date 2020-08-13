// Fill out your copyright notice in the Description page of Project Settings.


#include "GunActor.h"

// Sets default values
AGunActor::AGunActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Scene"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Mesh"));
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AGunActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetupGunDirection();

}

void AGunActor::SetupGunDirection()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		FVector OUT LineStart = Mesh->GetSocketTransform(FName("Muzzle")).GetLocation();
		FVector Direction = Mesh->GetSocketTransform(FName("Muzzle")).GetRotation().Vector();
		FVector OUT LineEnd = LineStart + Direction * 60000;

		//DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor::Red, false, 0.f, 0, 2.f);
		FHitResult Hit;
		bool Success = GetWorld()->LineTraceSingleByChannel(Hit, LineStart, LineEnd, ECollisionChannel::ECC_Visibility);

		if (Success)
		{
			FVector HitLocation = Hit.Location;
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *Hit.GetActor()->GetName());
			PlayerController->ProjectWorldLocationToScreen(HitLocation, ScreenLocation);
		}
	}
}

void AGunActor::SpawnProjectile()
{
	if (!Mesh) return;

	FVector MuzzleLocation = Mesh->GetSocketLocation(FName("Muzzle"));
	FRotator MuzzleRotation = Mesh->GetSocketRotation(FName("Muzzle"));

	GunProjectileActor = GetWorld()->SpawnActor<AGunProjectileActor>(GunProjectileActorClass, MuzzleLocation, MuzzleRotation);
}

void AGunActor::PullTrigger()
{
	UParticleSystemComponent* MuzzleFlashComponent = UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, FName("Muzzle"));
	if (!MuzzleFlashComponent) return;

	MuzzleFlashComponent->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	//MuzzleFlashComponent->SetRelativeLocation_Direct(FVector(50, 0, 0));

	SpawnProjectile();
}

void AGunActor::SetMaxBulletsCount(int32 Value)
{
	MaxBulletsCount = Value;
}

void AGunActor::SetMaxCountBulletsInMagazine(int32 Value)
{
	MaxCountBulletsInMagazine = Value;
}

float AGunActor::GetAutoFireRate()
{
	return AutoFireRate;
}

int32 AGunActor::GetMaxBulletsCount()
{
	return MaxBulletsCount;
}

int32 AGunActor::GetMaxCountBulletsInMagazine()
{
	return MaxCountBulletsInMagazine;
}

FVector2D AGunActor::GetScreenLocation()
{
	return ScreenLocation;
}

