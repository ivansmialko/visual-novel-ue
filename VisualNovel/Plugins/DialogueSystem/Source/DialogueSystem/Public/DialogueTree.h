// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <random>
#include "DialogueTree.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DIALOGUESYSTEM_API UDialogueTree : public UObject
{
	GENERATED_BODY()
public:
	UDialogueTree();

	UPROPERTY(EditAnywhere)
	int32 DialogueId;

	UPROPERTY(EditAnywhere)
	FText DialogueDescription;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TArray<TObjectPtr<class UDSDialogueNode>> AllNodes;

	UPROPERTY()
	TObjectPtr<UEdGraph> DialogueTreeGraph;
#endif

#if WITH_EDITOR
	virtual void PostInitProperties() override;
#endif

	UEdGraph* GetGraph();
};
