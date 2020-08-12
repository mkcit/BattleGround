// Fill out your copyright notice in the Description page of Project Settings.


#include "GunProjectileActor.h"

// Sets default values
AGunProjectileActor::AGunProjectileActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	Projectile = CreateDefaultSubobject<UStaticMeshComponent>(FName("Projectile"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movment"));

	//SetRootComponent(Root);

	//Projectile->SetupAttachment(Root);
	SetRootComponent(Projectile);


}

// Called when the game starts or when spawned
void AGunProjectileActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGunProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UProjectileMovementComponent* AGunProjectileActor::GetProjectileMovement()
{
	return ProjectileMovement;
}

