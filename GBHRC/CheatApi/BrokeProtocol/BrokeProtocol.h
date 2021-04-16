#pragma once
#include "Enum/PacketFlags.h"
#include "Enum/SvPacket.h"
#include "Mono/Mono.h"
#include "classes/Players/Players.h"
#include "classes/Managers/Managers.h"
#include "classes/Dictionary/Dictionary.h"

namespace BrokeProtocol
{
	Managers::ShManager* get_manager();
	Players::ShPlayer* GetLocalPlayer();
	Dictionary* GetPlayersCollection();

	void fire();
	
	void SendToServer(PacketFlags flags, BrokeProtocol::SvPacket packet, Mono::MonoArray* array);
	
	void show_local_message(char*text);
	void send_global_chat(char*text);
	void jump();
};



