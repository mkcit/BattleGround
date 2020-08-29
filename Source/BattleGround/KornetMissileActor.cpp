// Fill out your copyright notice in the Description page of Project Settings.


#include "KornetMissileActor.h"
#include "Kismet\GameplayStatics.h"

// Sets default values
AKornetMissileActor::AKornetMissileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Missile = CreateDefaultSubobject<UStaticMeshComponent>(FName("Missile"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(FName("Radial Force"));

	//ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movment"));

	/*ProjectileMovement->LimitVelocity(FVector(0, 0, 1));
	ProjectileMovement->Velocity = FVector(0, 0, 1);
	ProjectileMovement->UpdateComponentVelocity();*/

	SetRootComponent(Missile);
	SpringArm->SetupAttachment(Missile);
	Camera->SetupAttachment(SpringArm);
	RadialForceComponent->SetupAttachment(Missile);

	RadialForceComponent->bIgnoreOwningActor = true;
	RadialForceComponent->Radius = 3000.f;
	RadialForceComponent->ImpulseStrength = 20000.f;

}

// Called when the game starts or when spawned
void AKornetMissileActor::BeginPlay()
{
	Super::BeginPlay();

	if(Missile)
		Missile->OnComponentHit.AddDynamic(this, &AKornetMissileActor::OnHit);
}

// Called every frame
void AKornetMissileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Missile)
	{
		FVector DeltaLocation = Missile->GetForwardVector() * DeltaTime * MovementSpeedRate;
		//FRotator DeltaRotation(0, 0, DeltaTime * RotationSpeedRate);

		Missile->AddWorldOffset(DeltaLocation);
		//Missile->AddLocalRotation(DeltaRotation);

	}
}


UCameraComponent* AKornetMissileActor::GetCamera()
{
	return Camera;
}

void AKornetMissileActor::GuidMissile(FVector TargetLocation)
{
	if (!IsActorBeingDestroyed())
	{
		FVector MissileLocation = GetActorLocation();

		FRotator TargetRotation = ((TargetLocation - MissileLocation).GetSafeNormal()).Rotation();
		FRotator MissileRotation = GetActorForwardVector().Rotation();
		FRotator DeltaRotation = TargetRotation - MissileRotation;

		if (FMath::Abs(DeltaRotation.Yaw) <= MaxRotationAngleRange && FMath::Abs(DeltaRotation.Pitch) <= MaxRotationAngleRange)
			AddActorWorldRotation(DeltaRotation);
	}
}

void AKornetMissileActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if (!Missile) return;

	FVector Location = Missile->GetComponentTransform().GetLocation();
	FRotator Rotation = (Missile->GetComponentTransform().GetRotation().Vector() * -1).Rotation();
	FTransform Transofrm(Rotation, Location);

	UParticleSystemComponent* MissileCollisionEmitterComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MissileCollisionEmitter, Transofrm);

	if (MissileCollisionEmitterComponent)
		MissileCollisionEmitterComponent->SetWorldScale3D(FVector(1.f, 1.f, 1.f));

	if (RadialForceComponent)
		RadialForceComponent->FireImpulse();
	
	Destroy();
}

