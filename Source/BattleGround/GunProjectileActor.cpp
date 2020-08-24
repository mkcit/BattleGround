// Fill out your copyright notice in the Description page of Project Settings.


#include "GunProjectileActor.h"
#include "Kismet\GameplayStatics.h"

// Sets default values
AGunProjectileActor::AGunProjectileActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/*Root = CreateDefaultSubobject<USceneComponent>(FName("Scene"));
	SetRootComponent(Root);*/

	Projectile = CreateDefaultSubobject<UStaticMeshComponent>(FName("Projectile"));
	//Projectile->SetupAttachment(Root); 
	SetRootComponent(Projectile);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movment"));


	ProjectileMovement->InitialSpeed = 4000;
	ProjectileMovement->MaxSpeed = 4000;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.05f;
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

	if (!Projectile) return;

	//FTransform Transform = Projectile->GetComponentTransform();
	FVector Location = Projectile->GetComponentTransform().GetLocation();
	FRotator Rotation = (Projectile->GetComponentTransform().GetRotation().Vector() * -1).Rotation();
	FTransform Transofrm(Rotation, Location);

	UParticleSystemComponent* ProjectileCollisionEmitterComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ProjectileCollisionEmitter, Transofrm);
	
	if(ProjectileCollisionEmitterComponent)
		ProjectileCollisionEmitterComponent->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	
	Destroy();
}

