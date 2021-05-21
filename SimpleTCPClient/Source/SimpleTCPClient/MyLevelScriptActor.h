// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"

#include "Sockets.h"
#include "SocketSubsystem.h"
#include <string>
#include <Runtime/Networking/Public/Interfaces/IPv4/IPv4Address.h>
#include "MyLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()

class SIMPLETCPCLIENT_API AMyLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
public:

	void Ping() 
	{
		FSocket* socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

		FIPv4Address ip(127, 0, 0, 1);
		TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
		addr->SetIp(ip.Value);
		addr->SetPort(5213);

		bool connected = socket->Connect(*addr);

		UE_LOG(LogTemp, Warning, TEXT("Connected = %d"), connected);

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


	

	
};
