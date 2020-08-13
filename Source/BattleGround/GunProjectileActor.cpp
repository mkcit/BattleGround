// Fill out your copyright notice in the Description page of Project Settings.


#include "GunProjectileActor.h"

// Sets default values
AGunProjectileActor::AGunProjectileActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Scene"));
	SetRootComponent(Root);

	Projectile = CreateDefaultSubobject<UStaticMeshComponent>(FName("Projectile"));
	Projectile->SetupAttachment(Root);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movment"));


	ProjectileMovement->InitialSpeed = 3500;
	ProjectileMovement->MaxSpeed = 3500;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.1f;
	ProjectileMovement->SetActive(true);
	
	
}

// Called when the game starts or when spawned
void AGunProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	Projectile->OnComponentHit.AddDynamic(this, &AGunProjectileActor::OnHit);
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

void AGunProjectileActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *HitComp->GetName());

	/*if (!Projectile) return;

	Projectile->SetSimulatePhysics(true);
	Destroy();*/
}

