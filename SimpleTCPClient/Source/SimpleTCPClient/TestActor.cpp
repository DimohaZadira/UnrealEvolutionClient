// Fill out your copyright notice in the Description page of Project Settings.

#include "Sockets.h"
#include "SocketSubsystem.h"
#include "TestActor.h"
#include <string>
#include <Runtime/Networking/Public/Interfaces/IPv4/IPv4Address.h>
// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("ATestActor"));

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Hello"));

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
	
	
	
	
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

