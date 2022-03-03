// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStateUI.generated.h"

// �÷��� ȭ�鿡 �ʿ��� ������ 4�� �̰� �÷��̾ ���̴� X2 �� �ؼ� 8��
// �� �÷��̾ ���� �� ���� �� �̼��� ��� ����
// �� �÷��̾ ���� �� �� �տ� ���� �� ��� ����
// ���� �󸶳� �������� ��Ÿ���� ���α׷��� ��
// �÷��̾��� ID�� ��Ÿ���� ����
// MissionText �� �׻� �������, ���� ���� ���� ����
// FrontOfDoorText �� �� �տ� �� ���� ����, ���� ���� ���� ����
// �÷��̾�ID Text �� �׻� ����
// �Լ��� �ΰ��� �ʿ� �� �� ����
// 1. PlayerA �� ���� �� ��
// 2. PlayerB �� ���� �� ��
UCLASS()
class PRISONBREAK_API UPlayerStateUI : public UUserWidget
{
	GENERATED_BODY()

public:
	// �� �÷��̾ ���� �� ���� �� �̼��� ��� ����
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerA_MissionText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerB_MissionText;
	
	// �� �÷��̾ ���� �� �� �տ� ���� �� ��� ����
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerA_FrontOfDoorText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerB_FrontOfDoorText;

	// �÷��̾��� ID�� ��Ÿ���� ����
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerA_IDText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerB_IDText;

	// �Լ��� �ΰ��� �ʿ� �� �� ����
	// 1. PlayerA �� ���� �� ��
	// 2. PlayerB �� ���� �� ��
	void PlayerALockDoor();
	void PlayerBLockDoor();

	 // �߰������� PlayerID�� ��Ÿ���� �Լ��� �ۼ� �غ���
	 void AppearPlayerID();
};
