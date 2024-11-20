// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();	

	StartLocation = GetActorLocation();

	FString Name = GetName();

	// 1. �α� ī�װ� ���� ��������
	// 2. �󸶳� �ñ����� �α� ����
	// 3. �Լ� �� �Լ�, ����ؾ��� �ؽ�Ʈ
	// UE_LOG(LogTemp, Display, TEXT("Configured Moved Distance: %f"), MovedDistance);
	
	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	// Send platform back if gone too far
		// Reverse direction of motion if gone too far
	if (ShouldPlatformReturn()) {
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();

		StartLocation = StartLocation + (MoveDirection * MovedDistance);
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}

	else {
		// Move platform forwards
			// Get current location
		FVector CurrentLocation = GetActorLocation();
			// Add vector to that location
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
			// Set the location
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	/*
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation = CurrentRotation + (RotationVelocity * DeltaTime);
	SetActorRotation(CurrentRotation);

	�ܼ��� ȸ�� �߰��δ� ������ �����
	*/
	
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	// Check how far we've moved
	return GetDistanceMoved() > MovedDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}