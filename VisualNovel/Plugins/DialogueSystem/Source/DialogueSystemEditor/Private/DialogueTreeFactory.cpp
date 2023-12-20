// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTreeFactory.h"
#include "DialogueTree.h"

UDialogueTreeFactory::UDialogueTreeFactory()
{
	this->SupportedClass = UDialogueTree::StaticClass();
	this->bCreateNew = true;
}

UObject* UDialogueTreeFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UDialogueTree>(InParent, Class, Name, Flags);
}
