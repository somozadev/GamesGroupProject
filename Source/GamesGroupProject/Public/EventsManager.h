#pragma once
#include "CoreMinimal.h"
#include "EventsManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCustomEvent); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCustomEventOneParamString, FString, Param1);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCustomEventOneParamInt, int, Param1);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCustomEventOneParamIntInt, int, Param1, int , Param2);


UCLASS()
class GAMESGROUPPROJECT_API UEventsManager : public UObject
{
    GENERATED_BODY()

public:
    static UEventsManager* Get();

    void Subscribe(FName eventName, FOnCustomEvent::FDelegate& delegateEvent);
    void Unsubscribe(FName eventName, FOnCustomEvent::FDelegate& delegateEvent);
    void Invoke(FName EventName);
    
    void Subscribe(FName eventName, FOnCustomEventOneParamString::FDelegate& delegateEvent);
    void Unsubscribe(FName eventName, FOnCustomEventOneParamString::FDelegate& delegateEvent);
    void Invoke(FName eventName, FString param);
    
    void Subscribe(FName eventName, FOnCustomEventOneParamInt::FDelegate& delegateEvent);
    void Unsubscribe(FName eventName, FOnCustomEventOneParamInt::FDelegate& delegateEvent);
    void Invoke(FName eventName, int param);

    
    void Subscribe(FName eventName, FOnCustomEventOneParamIntInt::FDelegate& delegateEvent);
    void Unsubscribe(FName eventName, FOnCustomEventOneParamIntInt::FDelegate& delegateEvent);
    void Invoke(FName eventName, int param1, int param2);

    
    TMap<FName, FOnCustomEvent> EventMap;
    TMap<FName, FOnCustomEventOneParamString> EventMapOneParamString;
    TMap<FName, FOnCustomEventOneParamInt> EventMapOneParamInt;
    TMap<FName, FOnCustomEventOneParamIntInt> EventMapOneParamIntInt;
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