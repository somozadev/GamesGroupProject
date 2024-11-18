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

void UEventsManager::Subscribe(FName eventName, FOnCustomEventOneParamString::FDelegate& delegateEvent)
{
	if (!EventMapOneParamString.Contains(eventName))
	{
		EventMapOneParamString.Add(eventName, FOnCustomEventOneParamString());
	}

	UE_LOG(LogTemp, Warning, TEXT("EventsManager Subscribe Called"));
	EventMapOneParamString[eventName].Add(delegateEvent);
}

void UEventsManager::Unsubscribe(FName EventName, FOnCustomEventOneParamString::FDelegate& delegateEvent)
{
	if (EventMapOneParamString.Contains(EventName))
	{
		EventMapOneParamString[EventName].Remove(delegateEvent);
	}
}

void UEventsManager::Invoke(FName eventName, FString param)
{
	if (EventMapOneParamString.Contains(eventName))
	{
		EventMapOneParamString[eventName].Broadcast(param);
		UE_LOG(LogTemp, Warning, TEXT("Event %s invoked with param1: %s"), *eventName.ToString(), *param);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Event %s not found."), *eventName.ToString());
	}
}

void UEventsManager::Subscribe(FName eventName, FOnCustomEventOneParamInt::FDelegate& delegateEvent)
{
	if (!EventMapOneParamInt.Contains(eventName))
	{
		EventMapOneParamInt.Add(eventName, FOnCustomEventOneParamInt());
	}

	UE_LOG(LogTemp, Warning, TEXT("EventsManager Subscribe Called"));
	EventMapOneParamInt[eventName].Add(delegateEvent);
}

void UEventsManager::Unsubscribe(FName EventName, FOnCustomEventOneParamInt::FDelegate& delegateEvent)
{
	if (EventMapOneParamInt.Contains(EventName))
	{
		EventMapOneParamInt[EventName].Remove(delegateEvent);
	}
}

void UEventsManager::Invoke(FName eventName, int param)
{
	if (EventMapOneParamInt.Contains(eventName))
	{
		EventMapOneParamInt[eventName].Broadcast(param);
		UE_LOG(LogTemp, Warning, TEXT("Event %s invoked with param1: %d"), *eventName.ToString(), param);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Event %s not found."), *eventName.ToString());
	}
}

void UEventsManager::Subscribe(FName eventName, FOnCustomEventOneParamIntInt::FDelegate& delegateEvent)
{
	if (!EventMapOneParamIntInt.Contains(eventName))
	{
		EventMapOneParamIntInt.Add(eventName, FOnCustomEventOneParamIntInt());
	}

	UE_LOG(LogTemp, Warning, TEXT("EventsManager Subscribe Called"));
	EventMapOneParamIntInt[eventName].Add(delegateEvent);
}

void UEventsManager::Unsubscribe(FName EventName, FOnCustomEventOneParamIntInt::FDelegate& delegateEvent)
{
	if (EventMapOneParamIntInt.Contains(EventName))
	{
		EventMapOneParamIntInt[EventName].Remove(delegateEvent);
	}
}

void UEventsManager::Invoke(FName eventName, int param1, int param2)
{
	if (EventMapOneParamIntInt.Contains(eventName))
	{
		EventMapOneParamIntInt[eventName].Broadcast(param1,param2);
		UE_LOG(LogTemp, Warning, TEXT("Event %s invoked with param1: %d and param2: %d"), *eventName.ToString(), param1,param2);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Event %s not found."), *eventName.ToString());
	}
}

