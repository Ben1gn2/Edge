// Fill out your copyright notice in the Description page of Project Settings.


#include "EdgePlayerController.h"
#include "Edge_TheGame/HUD/Edge_HUD.h"
#include "Edge_TheGame/HUD/CharacterOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Edge_TheGame/Character/EdgeCharacter.h"

void AEdgePlayerController::BeginPlay()
{
	Super::BeginPlay();

	EdgeHUD = Cast<AEdge_HUD>(GetHUD());
}


void AEdgePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AEdgeCharacter* EdgeCharacter = Cast<AEdgeCharacter>(InPawn);
	if (EdgeCharacter)
	{
		SetHUDHealth(EdgeCharacter->GetHealth(), EdgeCharacter->GetMaxHealth());
	}
}

void AEdgePlayerController::SetHUDHealth(float Health, float MaxHealth)
{
	EdgeHUD = EdgeHUD == nullptr ? Cast<AEdge_HUD>(GetHUD()) : EdgeHUD;

	bool bHUDValid = EdgeHUD && EdgeHUD->CharacterOverlay && EdgeHUD->CharacterOverlay->HealthBar && EdgeHUD->CharacterOverlay->HealthText;
	if (bHUDValid)
	{
		const float HealthPercent = Health / MaxHealth;
		EdgeHUD->CharacterOverlay->HealthBar->SetPercent(HealthPercent);
		FString HealthText = FString::Printf(TEXT("%d/%d"), FMath::CeilToInt(Health), FMath::CeilToInt(MaxHealth));
		EdgeHUD->CharacterOverlay->HealthText->SetText(FText::FromString(HealthText));
	}
}

void AEdgePlayerController::SetHUDKills(float Score)
{
	EdgeHUD = EdgeHUD == nullptr ? Cast<AEdge_HUD>(GetHUD()) : EdgeHUD;
	bool bHUDValid = EdgeHUD && EdgeHUD->CharacterOverlay && EdgeHUD->CharacterOverlay->HealthBar && EdgeHUD->CharacterOverlay->KillAmount;
	if (bHUDValid)
	{
		FString ScoreText = FString::Printf(TEXT("%d"), FMath::FloorToInt(Score));
		EdgeHUD->CharacterOverlay->KillAmount->SetText(FText::FromString(ScoreText));
	}

}

void AEdgePlayerController::SetHUDDeath(int32 Value)
{
	EdgeHUD = EdgeHUD == nullptr ? Cast<AEdge_HUD>(GetHUD()) : EdgeHUD;
	bool bHUDValid = EdgeHUD && EdgeHUD->CharacterOverlay && EdgeHUD->CharacterOverlay->HealthBar && EdgeHUD->CharacterOverlay->DeathAmount;
	if (bHUDValid)
	{
		FString DeathText = FString::Printf(TEXT("%d"), Value);
		EdgeHUD->CharacterOverlay->DeathAmount->SetText(FText::FromString(DeathText));
	}
}
