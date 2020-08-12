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

}

void AGunActor::SpawnProjectile()
{
	if (!Mesh) return;

	FVector MuzzleLocation = Mesh->GetSocketLocation(FName("Projectile"));
	FRotator MuzzleRotation = Mesh->GetSocketRotation(FName("Projectile"));


	GunProjectileActor = GetWorld()->SpawnActor<AGunProjectileActor>(GunProjectileActorClass, MuzzleLocation, MuzzleRotation);

	UProjectileMovementComponent* ProjectileMovement = GunProjectileActor->GetProjectileMovement();
	if (!ProjectileMovement) return;


	ProjectileMovement->Activate(true);
}

void AGunActor::PullTrigger()
{
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

