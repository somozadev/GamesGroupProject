#include "EventsManager.h"

// Initialize the static instance
UEventsManager* UEventsManager::Instance = nullptr;

// Access the singleton instance
UEventsManager* UEventsManager::Get()
{
	if (!Instance)
	{
		Instance = NewObject<UEventsManager>();
		Instance->AddToRoot(); // Prevent garbage collection
	}
	UE_LOG(LogTemp, Warning, TEXT("EventsManager Get Called"));

	return Instance;
}

void UEventsManager::Subscribe(FName eventName, FOnCustomEvent::FDelegate& delegateEvent)
{
	if (!EventMap.Contains(eventName))
	{
		EventMap.Add(eventName, FOnCustomEvent());
	}

	UE_LOG(LogTemp, Warning, TEXT("EventsManager Subscribe Called"));
	EventMap[eventName].Add(delegateEvent);
}

void UEventsManager::Unsubscribe(FName eventName, FOnCustomEvent::FDelegate& delegateEvent)
{
	if (EventMap.Contains(eventName))
	{
		EventMap[eventName].Remove(delegateEvent);
	}
}

void UEventsManager::Invoke(FName eventName)
{
	if (EventMap.Contains(eventName))
	{
		EventMap[eventName].Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("Event %s invoked."), *eventName.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("asadsdad"));
	}
}

void UEventsManager::Subscribe(FName eventName, FOnCustomEventOneParam::FDelegate& delegateEvent)
{
	if (!EventMapOneParam.Contains(eventName))
	{
		EventMapOneParam.Add(eventName, FOnCustomEventOneParam());
	}

	UE_LOG(LogTemp, Warning, TEXT("EventsManager Subscribe Called"));
	EventMapOneParam[eventName].Add(delegateEvent);
}

void UEventsManager::Unsubscribe(FName EventName, FOnCustomEventOneParam::FDelegate& delegateEvent)
{
	if (EventMapOneParam.Contains(EventName))
	{
		EventMapOneParam[EventName].Remove(delegateEvent);
	}
}

void UEventsManager::Invoke(FName eventName, FString param)
{
	if (EventMapOneParam.Contains(eventName))
	{
		EventMapOneParam[eventName].Broadcast(param);
		UE_LOG(LogTemp, Warning, TEXT("Event %s invoked with param1: %s"), *eventName.ToString(), *param);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Event %s not found."), *eventName.ToString());
	}
}
