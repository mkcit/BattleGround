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

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(FName("Rotating Movment"));

	SetRootComponent(Missile);
	SpringArm->SetupAttachment(Missile);
	Camera->SetupAttachment(SpringArm);
	RadialForceComponent->SetupAttachment(Missile);

	RadialForceComponent->bIgnoreOwningActor = true;
	RadialForceComponent->Radius = 1500.f;
	RadialForceComponent->ImpulseStrength = 50000.f;

	RotatingMovementComponent->SetAutoActivate(false);
	RotatingMovementComponent->RotationRate = FRotator(0, 0, 1000);
	RotatingMovementComponent->PivotTranslation = FVector(0, 0, 20);


}

// Called when the game starts or when spawned
void AKornetMissileActor::BeginPlay()
{
	Super::BeginPlay();

	if(Missile)
		Missile->OnComponentHit.AddDynamic(this, &AKornetMissileActor::OnHit);

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AKornetMissileActor::ActivateMissileRotation, 0.08f, false);
}

void AKornetMissileActor::ActivateMissileRotation()
{
	if (RotatingMovementComponent)
		RotatingMovementComponent->Activate(true);
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

