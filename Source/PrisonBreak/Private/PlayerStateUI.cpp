// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateUI.h"
#include "PlayerA.h"
#include "PlayerB.h"
#include <Components/TextBlock.h>

// �÷��̾�A�� ���� ���� �ְų� ���� ���� ���� �϶�
void UPlayerStateUI::PlayerALockDoor()
{
	//// �÷��̾� �̼� ����
	/*if (PlayerA_MissionText && PlayerB_MissionText)
	{
		FString playerAMissionText = FString(TEXT("���������� ��Ű�� �ʰ� ���� ���ÿ�"));
		PlayerA_MissionText->SetText(FText::FromString(playerAMissionText));

		FString playerBMissionText = FString::Printf(TEXT("��Ʈ�ʰ� ���� ���� ���� ���� ���ų� �������� ��ȭ�Ͻÿ�"));
		PlayerB_MissionText->SetText(FText::FromString(playerBMissionText));
	}*/

	//// �÷��̾� �� �տ� ���� �� ��ȣ �ۿ� Ű�� �˷��ִ� ����
	//if (PlayerB_FrontOfDoorText && PlayerB_FrontOfDoorText)
	//{
	//	FString playerADoorText = FString::Printf(TEXT("FŰ�� ������ ������ ���� ���ϴ�."));
	//	PlayerA_FrontOfDoorText->SetText(FText::FromString(playerADoorText));

	//	FString playerBDoorText = FString::Printf(TEXT("KŰ�� ���� ���� ���ʽÿ�."));
	//	PlayerB_FrontOfDoorText->SetText(FText::FromString(playerBDoorText));
	//}
}

// �÷��̾�B�� ���� ���� �ְų� ���� ���� ���� �϶�
void UPlayerStateUI::PlayerBLockDoor()
{
	//// �÷��̾� �̼� ����
	//if (PlayerA_MissionText && PlayerB_MissionText)
	//{
	//	FString playerAMissionText = FString::Printf(TEXT("��Ʈ�ʰ� ���� ���� ���� ���� ���ų� �������� ��ȭ�Ͻÿ�"));
	//	PlayerA_MissionText->SetText(FText::FromString(playerAMissionText));

	//	FString playerBMissionText = FString::Printf(TEXT("���������� ��Ű�� �ʰ� ���� ���ÿ�"));
	//	PlayerB_MissionText->SetText(FText::FromString(playerBMissionText));
	//}

	//// �÷��̾� �� �տ� ���� �� ��ȣ �ۿ� Ű�� �˷��ִ� ����
	//if (PlayerB_FrontOfDoorText && PlayerB_FrontOfDoorText)
	//{
	//	FString playerADoorText = FString::Printf(TEXT("EŰ�� ���� ���� ���ʽÿ�."));
	//	PlayerA_FrontOfDoorText->SetText(FText::FromString(playerADoorText));

	//	FString playerBDoorText = FString::Printf(TEXT("LŰ�� ������ ������ ���� ���ϴ�."));
	//	PlayerB_FrontOfDoorText->SetText(FText::FromString(playerBDoorText));
	//}
}

void UPlayerStateUI::AppearPlayerID()
{
}
