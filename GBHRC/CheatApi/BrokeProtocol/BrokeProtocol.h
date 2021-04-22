#pragma once
#include "Enum/PacketFlags.h"
#include "Enum/SvPacket.h"
#include "Mono/Mono.h"
#include "classes/Players/Players.h"
#include "classes/Managers/Managers.h"
#include "classes/Collections/KeyedCollection.h"

namespace BrokeProtocol
{
	Structs::MainCamera* get_camera();
	
	Structs::Evaluator* get_evaluator();
	Structs::GlobalTypes* get_global_types();
	Managers::ShManager* get_manager();
	Players::ShPlayer* GetLocalPlayer();
	Collections::KeyedCollection<Players::ShPlayer*>* GetPlayersCollection();

	void fire();
	
	void SendToServer(PacketFlags flags, BrokeProtocol::SvPacket packet, Mono::MonoArray* array);
	
	void show_local_message(char*text);
	void send_global_chat(char*text);
	void jump();
	void ShowTextMenu(float xMin, float yMin, float xMax, float yMax,const char* title,const char* text);
	// shows panel in top-right angle
	void ShowTextPanel(const char* text);
};



