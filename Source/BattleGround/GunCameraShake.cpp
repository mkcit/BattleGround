// Fill out your copyright notice in the Description page of Project Settings.


#include "GunCameraShake.h"

UGunCameraShake::UGunCameraShake()
{
	OscillationDuration = 0.2;
	OscillationBlendInTime = 0.05;
	OscillationBlendOutTime = 0.05;

	RotOscillation.Pitch.Amplitude = FMath::RandRange(1.f, 3.f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(1.f, 3.f);
	RotOscillation.Yaw.Amplitude = FMath::RandRange(1.f, 2.f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(1.f, 2.f);
}