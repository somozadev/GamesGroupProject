// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "EventsManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCustomEvent); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCustomEventOneParam, FString, Param1);


UCLASS()
class GAMESGROUPPROJECT_API UEventsManager : public UObject
{
    GENERATED_BODY()

public:
    // Singleton instance access
    static UEventsManager* Get();

    void Subscribe(FName eventName, FOnCustomEvent::FDelegate& delegateEvent);
    void Unsubscribe(FName eventName, FOnCustomEvent::FDelegate& delegateEvent);
    void Invoke(FName EventName);
    
    void Subscribe(FName eventName, FOnCustomEventOneParam::FDelegate& delegateEvent);
    void Unsubscribe(FName eventName, FOnCustomEventOneParam::FDelegate& delegateEvent);
    void Invoke(FName eventName, FString param);

    
    TMap<FName, FOnCustomEvent> EventMap;
    TMap<FName, FOnCustomEventOneParam> EventMapOneParam;
private:
    // Singleton instance
    static UEventsManager* Instance;

    /*
    * Example of use: 
    * inside the beginPlay of the c++ class i want to use the event manager 
    *
    *	FOnCustomEvent eventDelegate = FOnCustomEvent();
        eventDelegate.AddDynamic(this, &AInteractable::ExampleMethodThatWillBeCalledWhenEventGetsInvoked);
        UEventsManager::Get()->EventMap.Add("EventName", eventDelegate);
    *
    *
        Then, to invoke the even simply call: 
        UEventsManager::Get()->Invoke("EventNameToInvoke")
    */

    
};