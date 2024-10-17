#include "EventsManager.h"

// Initialize the static instance
UEventsManager* UEventsManager::Instance = nullptr;

// Access the singleton instance
UEventsManager* UEventsManager::Get()
{
    if (!Instance)
    {
        Instance = NewObject<UEventsManager>();
        Instance->AddToRoot();  // Prevent garbage collection
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

void UEventsManager::Unsubscribe(FName EventName, FOnCustomEvent::FDelegate& Delegate)
{
    if (EventMap.Contains(EventName))
    {
        EventMap[EventName].Remove(Delegate);
    }
}
void UEventsManager::Invoke(FName EventName)
{
    if (EventMap.Contains(EventName))
    {
        EventMap[EventName].Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Event %s invoked."), *EventName.ToString());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("asadsdad"));
    }

}

