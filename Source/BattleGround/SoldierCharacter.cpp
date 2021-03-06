// Fill out your copyright notice in the Description page of Project Settings.
#include "SoldierCharacter.h"
#include "SoldierPlayerController.h"


// Sets default values
ASoldierCharacter::ASoldierCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASoldierCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<ASoldierPlayerController>(GetController());

	StoreCameras();

	GunActor = GetWorld()->SpawnActor<AGunActor>(GunActorClass);
	if (GunActor)
	{
		GunActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("GunSocket"));
		GunActor->SetOwner(this);

		CurrentBulletsCount = GunActor->GetMaxBulletsCount();
		CurrentBulletsCountInMagazine = GunActor->GetMaxCountBulletsInMagazine();
	}


}

// Called every frame
void ASoldierCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FireGun();

	//if other actor overlapped by pawn
	PrimitiveOverlappingComponent = nullptr;
	TArray<UPrimitiveComponent*> OverlappingComponents;
	GetOverlappingComponents(OverlappingComponents);
	IsSoldierInGunArea = false;
	for (int i = 0; i < OverlappingComponents.Num(); i++) {
		IsSoldierInGunArea = true;
		PrimitiveOverlappingComponent = OverlappingComponents[i];
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *PrimitiveOverlappingComponent->GetName());
	}
	//connect other with pawn

}

// Called to bind functionality to input
void ASoldierCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ASoldierCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASoldierCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ASoldierCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &ASoldierCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("IncreaseMovementRate"), this, &ASoldierCharacter::IncreaseMovementRate);
	PlayerInputComponent->BindAxis(TEXT("DecreaseMovementRate"), this, &ASoldierCharacter::DecreaseMovementRate);


	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &ASoldierCharacter::Crouch);
	PlayerInputComponent->BindAction(TEXT("ShowFirstPersonView"), EInputEvent::IE_Pressed, this, &ASoldierCharacter::ShowFirstPersonView);
	PlayerInputComponent->BindAction(TEXT("ShowThirdPersonView"), EInputEvent::IE_Pressed, this, &ASoldierCharacter::ShowThirdPersonView);
	PlayerInputComponent->BindAction(TEXT("ShowDownSightView"), EInputEvent::IE_Pressed, this, &ASoldierCharacter::ShowDownSightView);
	PlayerInputComponent->BindAction(TEXT("ShowMissileView"), EInputEvent::IE_Pressed, this, &ASoldierCharacter::ShowMissileView);
	
	PlayerInputComponent->BindAction(TEXT("PullLeaveTrigger"), EInputEvent::IE_Pressed, this, &ASoldierCharacter::PullTrigger);
	PlayerInputComponent->BindAction(TEXT("PullLeaveTrigger"), EInputEvent::IE_Released, this, &ASoldierCharacter::LeaveTrigger);
	PlayerInputComponent->BindAction(TEXT("ReloadGunMagazine"), EInputEvent::IE_Pressed, this, &ASoldierCharacter::ReloadGunMagazine);
	
	PlayerInputComponent->BindAction(TEXT("PickUpWeapon"), EInputEvent::IE_Pressed, this, &ASoldierCharacter::PickUpWeapon);
	PlayerInputComponent->BindAction(TEXT("LeaveWeapon"), EInputEvent::IE_Pressed, this, &ASoldierCharacter::LeaveWeapon);


}

void ASoldierCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue * CharacterMovementSpeedRate);
}

void ASoldierCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue * CharacterMovementSpeedRate);
}

void ASoldierCharacter::LookUp(float AxisValue)
{
	if (CanControlOverlappingActor && KornetSystemActor)
	{
		USceneComponent* UpDownScene = KornetSystemActor->GetUpDownScene();
		if (UpDownScene && KornetSystemActor)
		{
			UpDownScene->AddLocalRotation(FRotator(AxisValue * DefaultCharacterRotationSpeedRate * GetWorld()->GetDeltaSeconds() * -1, 0, 0));
			KornetSystemActor->ActiveNavigatorSystem();
		}
	}
	else
	{
		AddControllerPitchInput(AxisValue * DefaultCharacterRotationSpeedRate * GetWorld()->GetDeltaSeconds());
		CalculateTheAngle();
	}
	
}

void ASoldierCharacter::LookRight(float AxisValue)
{
	if (CanControlOverlappingActor && KornetSystemActor)
	{
		//UStaticMeshComponent* VisionSystem = KornetSystemActor->GetVisionSystem();
		USceneComponent* RightLeftScene = KornetSystemActor->GetRightLeftScene();
		if (RightLeftScene && KornetSystemActor)
		{
			RightLeftScene->AddLocalRotation(FRotator(0, AxisValue * DefaultCharacterRotationSpeedRate * GetWorld()->GetDeltaSeconds(), 0));

			KornetSystemActor->ActiveNavigatorSystem();
		}
	}
	else
	{
		AddControllerYawInput(AxisValue * DefaultCharacterRotationSpeedRate * GetWorld()->GetDeltaSeconds());
	}
}

void ASoldierCharacter::IncreaseMovementRate(float AxisValue)
{
	if (!IsDecreasingCharacterMovementSpeedRate)
	{
		if (AxisValue > 0)
		{
			IsIncreasingCharacterMovementSpeedRate = true; 
			CharacterMovementSpeedRate = DefaultCharacterMovementSpeedRate * GetSpeedFactor()[0];
			//CharacterMovementSpeedRate = 0.9f;
		}
		else
		{
			IsIncreasingCharacterMovementSpeedRate = false;
			CharacterMovementSpeedRate = DefaultCharacterMovementSpeedRate;
		}
	}
}

void ASoldierCharacter::DecreaseMovementRate(float AxisValue)
{
	if (!IsIncreasingCharacterMovementSpeedRate)
	{
		if (AxisValue > 0)
		{
			IsDecreasingCharacterMovementSpeedRate = true;
			CharacterMovementSpeedRate = DefaultCharacterMovementSpeedRate * GetSpeedFactor()[1];
			//CharacterMovementSpeedRate = 0.3f;
		}
		else
		{
			IsDecreasingCharacterMovementSpeedRate = false;
			CharacterMovementSpeedRate = DefaultCharacterMovementSpeedRate;
		}
	}
}

void ASoldierCharacter::PickUpWeapon()
{
	if (IsSoldierInGunArea && PrimitiveOverlappingComponent)
	{
		AActor* Actor = PrimitiveOverlappingComponent->GetOwner();
		KornetSystemActor = Cast< AKornetSystemActor>(Actor);
		if (KornetSystemActor && PlayerController)
		{
			PlayerController->ShowLauncherMissileSystemWidget();
			PlayerController->SetViewTargetWithBlend(KornetSystemActor);
			CanControlOverlappingActor = true;
		}
	}
}

void ASoldierCharacter::LeaveWeapon()
{
	if (PlayerController)
	{
		PlayerController->ShowGunWidget();
		PlayerController->SetViewTargetWithBlend(this);
		CanControlOverlappingActor = false;
	}
}

void ASoldierCharacter::PullTrigger()
{
	if (!CanControlOverlappingActor)
		IsAutoGunTriggerPulled = true;
	else
	{
		if (KornetSystemActor)
		{
			KornetSystemActor->Fire();
		}
	}
}

void ASoldierCharacter::LeaveTrigger()
{
	IsAutoGunTriggerPulled = false;
}

void ASoldierCharacter::ReloadGunMagazine()
{
	if (GunActor)
	{
		int32 NeededBulletsToFillMagazine = GunActor->GetMaxCountBulletsInMagazine() - CurrentBulletsCountInMagazine;
		
		if (NeededBulletsToFillMagazine > 0)
		{
			if (CurrentBulletsCount >= NeededBulletsToFillMagazine)
			{
				ReloadingMagazineNow = true;
				CurrentBulletsCountInMagazine += NeededBulletsToFillMagazine;
				CurrentBulletsCount -= NeededBulletsToFillMagazine;
			}
			else if (CurrentBulletsCount > 0 && CurrentBulletsCount < NeededBulletsToFillMagazine)
			{
				ReloadingMagazineNow = true;
				CurrentBulletsCountInMagazine += NeededBulletsToFillMagazine;
				CurrentBulletsCount = 0;
			}

			FTimerHandle OUT TimerHandle;
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASoldierCharacter::StopReloadingMagazine, 3.f, false);
		}
	}
}

void ASoldierCharacter::StopReloadingMagazine()
{
	ReloadingMagazineNow = false;
	ShowBulletsCountOnScreen();
}

void ASoldierCharacter::Crouch()
{
	IsSoldierCharacterCrouchingNow = !IsSoldierCharacterCrouchingNow;
	if (IsSoldierCharacterCrouchingNow)
	{
		DefaultCharacterMovementSpeedRate = 0.25f;
	}
	else
	{
		DefaultCharacterMovementSpeedRate = 0.5f;
	}
}

void ASoldierCharacter::FireGun()
{
	// If Auto Gun is Picked
	
	if (IsAutoGunTriggerPulled)
	{
		if ( !CanControlOverlappingActor && GunActor)
		{
			CurrentSecond = GetWorld()->GetTimeSeconds();
			if ((CurrentSecond - LastSecond) >= GunActor->GetAutoFireRate())
			{
				if (CurrentBulletsCountInMagazine > 0)
				{
					//UE_LOG(LogTemp, Warning, TEXT("PullTrigger"));
					//PlayerController->PlayerCameraManager->PlayCameraShake(CameraShakeClass);
					GunActor->PullTrigger();
					CurrentBulletsCountInMagazine--;
				}
				LastSecond = CurrentSecond;

				ShowBulletsCountOnScreen();
			}
		}
	}
	
}

AGunActor* ASoldierCharacter::GetGunActor()
{
	return GunActor;
}

float ASoldierCharacter::GetSoldierCharacterSpeed()
{
	return GetVelocity().Size();
}

float ASoldierCharacter::GetSoldierCharacterAngle()
{
	FVector Direction = GetVelocity().GetSafeNormal();
	FTransform Transform = GetActorTransform();
	FVector LocalDirection = UKismetMathLibrary::InverseTransformDirection(Transform, Direction);
	FRotator LocalRotation = LocalDirection.Rotation();
	return LocalRotation.Yaw;
}


bool ASoldierCharacter::GetIfSoldierCharacterIsCrouchingNow()
{
	return IsSoldierCharacterCrouchingNow;
}

bool ASoldierCharacter::GetIfSoldierCharacterIsReloadingNow()
{
	return ReloadingMagazineNow;
}

void ASoldierCharacter::ShowFirstPersonView()
{
	FirstPersonViewCamera = Cameras.Find(FName("FirstPersonViewCamera"));
	if (FirstPersonViewCamera)
	{
		DeActivateAllCameras();
		(*FirstPersonViewCamera)->SetActive(true);
	}
}

void ASoldierCharacter::ShowThirdPersonView()
{
	ThirdPersonViewCamera = Cameras.Find(FName("ThirdPersonViewCamera"));
	if (ThirdPersonViewCamera)
	{
		DeActivateAllCameras();
		(*ThirdPersonViewCamera)->SetActive(true);
	}
}

void ASoldierCharacter::ShowDownSightView()
{
	DownSightViewCamera = Cameras.Find(FName("DownSightViewCamera"));

	if (DownSightViewCamera)
	{
		DeActivateAllCameras();
		(*DownSightViewCamera)->SetActive(true);
	}
}

void ASoldierCharacter::ShowMissileView()
{
	if (KornetSystemActor)
	{
		AKornetMissileActor* Missile = KornetSystemActor->GetLastFiredMissile();
		if (Missile && PlayerController)
		{
			PlayerController->SetViewTargetWithBlend(Missile);
		}
	}
}

/*****************************************************/

void ASoldierCharacter::StoreCameras()
{
	Cameras.Empty();

	TArray<UActorComponent*> CamerasList = GetComponentsByClass(UCameraComponent::StaticClass());
	for (int i = 0; i < CamerasList.Num(); i++)
	{
		UCameraComponent* Camera = Cast<UCameraComponent>(CamerasList[i]);
		if (Camera)
			Cameras.Add(FName(Camera->GetName()), Camera);
	}
}

void ASoldierCharacter::DeActivateAllCameras()
{
	bUseControllerRotationYaw = true;
	for (const TPair<FName, UCameraComponent*>& Camera : Cameras)
	{
		if (Camera.Value != nullptr)
			Camera.Value->SetActive(false);
	}
}

float* ASoldierCharacter::GetSpeedFactor()
{
	static float Speedrate[2];
	if (IsSoldierCharacterCrouchingNow)
	{
		Speedrate[0] = 3.7f; // Increasing
		Speedrate[1] = 1.f; // Decreasing
	}
	else
	{
		Speedrate[0] = 1.8f; // Increasing
		Speedrate[1] = 0.6f; // Decreasing
	}
	return Speedrate;
}

FVector2D ASoldierCharacter::GetScreenPosition()
{
	return ScreenLocation;
}

void ASoldierCharacter::CalculateTheAngle()
{
	FRotator EyeRotation = GetControlRotation();
	float UpDownAngle = EyeRotation.Pitch;

	if (UpDownAngle > 180)
		BoneRotatonAngle = 360 - UpDownAngle;
	else
		BoneRotatonAngle = UpDownAngle * (-1);

	// We have three bones
	BoneRotatonAngle = (BoneRotatonAngle / 3);
}

FRotator ASoldierCharacter::GetBoneRotation() const
{
	FRotator BoneRotation(0, 0, BoneRotatonAngle);

	return BoneRotation;
}

void ASoldierCharacter::ShowBulletsCountOnScreen()
{

	if (PlayerController)
	{
		PlayerController->ShowBulletsCountOnScreen(CurrentBulletsCount, CurrentBulletsCountInMagazine);
	}
}
