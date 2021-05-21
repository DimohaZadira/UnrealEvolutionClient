// Fill out your copyright notice in the Description page of Project Settings.
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))


#include "PingPlease.h"
#include "Engine/TriggerBox.h"
#include "DrawDebugHelpers.h"

#include "Sockets.h"
#include "SocketSubsystem.h"
#include <string>
#include <Runtime/Networking/Public/Interfaces/IPv4/IPv4Address.h>



APingPlease::APingPlease()
{
    //Register Events
    OnActorBeginOverlap.AddDynamic(this, &APingPlease::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &APingPlease::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APingPlease::BeginPlay()
{
    Super::BeginPlay();

    DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);

}

void APingPlease::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    // check if Actors do not equal nullptr and that 
    if (OtherActor && (OtherActor != this)) {
        // print to screen using above defined method when actor enters trigger box
        print("Overlap Begin");

		FSocket* socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

		FIPv4Address ip(127, 0, 0, 1);
		TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
		addr->SetIp(ip.Value);
		addr->SetPort(5213);

		bool connected = socket->Connect(*addr);

		UE_LOG(LogTemp, Warning, TEXT("Connected = %d"), connected);


		if (connected)
		{
			char buf[1024];
			int32 bytes_read = 0;
			socket->Recv(reinterpret_cast<uint8*>(buf), sizeof(buf), bytes_read);

			UE_LOG(LogTemp, Warning, TEXT("Recieved = %s, %d bytes read"), reinterpret_cast<const char*>(buf), bytes_read);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Did not recieve anything :c"));
		}

        printFString("Overlapped Actor = %s", *OverlappedActor->GetName());
    }
}

void APingPlease::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
    if (OtherActor && (OtherActor != this)) {
        // print to screen using above defined method when actor leaves trigger box
        print("Overlap Ended");
        printFString("%s has left the Trigger Box", *OtherActor->GetName());
    }
}