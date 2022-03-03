// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateUI.h"
#include "PlayerA.h"
#include "PlayerB.h"
#include <Components/TextBlock.h>

// 플레이어A가 문을 열고 있거나 문을 여는 상태 일때
void UPlayerStateUI::PlayerALockDoor()
{
	//// 플레이어 미션 문구
	/*if (PlayerA_MissionText && PlayerB_MissionText)
	{
		FString playerAMissionText = FString(TEXT("교도관에게 들키지 않게 문을 여시오"));
		PlayerA_MissionText->SetText(FText::FromString(playerAMissionText));

		FString playerBMissionText = FString::Printf(TEXT("파트너가 문을 여는 동안 망을 보거나 교도관과 대화하시오"));
		PlayerB_MissionText->SetText(FText::FromString(playerBMissionText));
	}*/

	//// 플레이어 문 앞에 섰을 때 상호 작용 키를 알려주는 문구
	//if (PlayerB_FrontOfDoorText && PlayerB_FrontOfDoorText)
	//{
	//	FString playerADoorText = FString::Printf(TEXT("F키를 누르고 있으면 문을 엽니다."));
	//	PlayerA_FrontOfDoorText->SetText(FText::FromString(playerADoorText));

	//	FString playerBDoorText = FString::Printf(TEXT("K키를 눌러 망을 보십시오."));
	//	PlayerB_FrontOfDoorText->SetText(FText::FromString(playerBDoorText));
	//}
}

// 플레이어B가 문을 열고 있거나 문을 여는 상태 일때
void UPlayerStateUI::PlayerBLockDoor()
{
	//// 플레이어 미션 문구
	//if (PlayerA_MissionText && PlayerB_MissionText)
	//{
	//	FString playerAMissionText = FString::Printf(TEXT("파트너가 문을 여는 동안 망을 보거나 교도관과 대화하시오"));
	//	PlayerA_MissionText->SetText(FText::FromString(playerAMissionText));

	//	FString playerBMissionText = FString::Printf(TEXT("교도관에게 들키지 않게 문을 여시오"));
	//	PlayerB_MissionText->SetText(FText::FromString(playerBMissionText));
	//}

	//// 플레이어 문 앞에 섰을 때 상호 작용 키를 알려주는 문구
	//if (PlayerB_FrontOfDoorText && PlayerB_FrontOfDoorText)
	//{
	//	FString playerADoorText = FString::Printf(TEXT("E키를 눌러 망을 보십시오."));
	//	PlayerA_FrontOfDoorText->SetText(FText::FromString(playerADoorText));

	//	FString playerBDoorText = FString::Printf(TEXT("L키를 누르고 있으면 문을 엽니다."));
	//	PlayerB_FrontOfDoorText->SetText(FText::FromString(playerBDoorText));
	//}
}

void UPlayerStateUI::AppearPlayerID()
{
}
