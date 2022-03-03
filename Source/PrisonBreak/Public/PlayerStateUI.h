// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStateUI.generated.h"

// 플레이 화면에 필요한 정보는 4개 이고 플레이어가 둘이니 X2 를 해서 8개
// 각 플레이어가 상태 별 수행 할 미션을 띄울 문구
// 각 플레이어가 상태 별 문 앞에 섰을 때 띄울 문구
// 문을 얼마나 열었는지 나타내는 프로그래스 바
// 플레이어의 ID를 나타내는 문구
// MissionText 는 항상 띄우지만, 상태 별로 문구 변경
// FrontOfDoorText 는 문 앞에 갈 때만 띄우고, 상태 별로 문구 변경
// 플레이어ID Text 는 항상 띄우기
// 함수는 두개가 필요 할 거 같다
// 1. PlayerA 가 문을 열 때
// 2. PlayerB 가 문을 열 때
UCLASS()
class PRISONBREAK_API UPlayerStateUI : public UUserWidget
{
	GENERATED_BODY()

public:
	// 각 플레이어가 상태 별 수행 할 미션을 띄울 문구
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerA_MissionText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerB_MissionText;
	
	// 각 플레이어가 상태 별 문 앞에 섰을 때 띄울 문구
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerA_FrontOfDoorText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerB_FrontOfDoorText;

	// 플레이어의 ID를 나타내는 문구
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerA_IDText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerB_IDText;

	// 함수는 두개가 필요 할 거 같다
	// 1. PlayerA 가 문을 열 때
	// 2. PlayerB 가 문을 열 때
	void PlayerALockDoor();
	void PlayerBLockDoor();

	 // 추가적으로 PlayerID를 나타내는 함수도 작성 해보자
	 void AppearPlayerID();
};
