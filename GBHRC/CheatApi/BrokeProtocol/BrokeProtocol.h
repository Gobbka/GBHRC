#pragma once
#include "BPStructs.h"
#include "Enum/PacketFlags.h"
#include "Enum/SvPacket.h"
#include "Mono/Mono.h"
#include "classes/ICollection/ICollection.h"

namespace BrokeProtocol
{
	ShManager* get_manager();
	ShPlayer* GetLocalPlayer();
	void* GetPlayersCollection();

	void fire();
	
	void SendToServer(PacketFlags flags, BrokeProtocol::SvPacket packet, Mono::MonoArray* array);
	
	void show_local_message(char*text);
	void send_global_chat(char*text);
};



