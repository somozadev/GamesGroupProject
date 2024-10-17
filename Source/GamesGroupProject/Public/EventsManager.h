// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "EventsManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCustomEvent); 

UCLASS()
class GAMESGROUPPROJECT_API UEventsManager : public UObject
{
    GENERATED_BODY()

public:
    // Singleton instance access
    static UEventsManager* Get();

    void Subscribe(FName eventName, FOnCustomEvent::FDelegate& delegateEvent);
    void Unsubscribe(FName EventName, FOnCustomEvent::FDelegate& Delegate);
    void Invoke(FName EventName);

    TMap<FName, FOnCustomEvent> EventMap;
private:
    // Singleton instance
    static UEventsManager* Instance;

protected:
};