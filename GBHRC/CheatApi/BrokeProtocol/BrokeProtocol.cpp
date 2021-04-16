#include "BrokeProtocol.h"
#include "../../includes/win.h"
#include "../../includes/logger.h"
#include "Mono/Mono.h"
#include "Mono/Images/Script/ScriptImage.h"

#define STATIC_METHOD(name,inc_namespace) static Mono::MonoMethod* pMethod; \
	if(pMethod == nullptr) pMethod = Mono::ScriptImage::mono_get_method_from_name(name, inc_namespace)

BrokeProtocol::Managers::ShManager* BrokeProtocol::get_manager()
{
    static Managers::ShManager* manager;

	if(manager==nullptr)
	{
        auto* const unity_player = GetModuleHandle(L"mono-2.0-bdwgc.dll");
        manager = (Managers::ShManager*)(*(size_t*)(*(size_t*)(*(size_t*)(*(size_t*)((size_t)unity_player + 0X4A7518) + 0X360) + 0X68) + 0X160)+0x280);
	}
	
    return reinterpret_cast<Managers::ShManager*>(manager);
}

BrokeProtocol::Players::ShPlayer* BrokeProtocol::GetLocalPlayer()
{
    auto* manager = get_manager();
    if (manager->host == nullptr)
    {
        DEBUG_LOG("U ARE NOT IN GAME!");
        return nullptr;
    }

    return get_manager()->clManager->myPlayer;
}

Dictionary* BrokeProtocol::GetPlayersCollection()
{
    static Dictionary* players;

	if(players==nullptr)
	{
        auto* image = Mono::get_script_image();
        auto* method_desc = Mono::mono_method_desc_new("BrokeProtocol.Collections.EntityCollections:n()", true);

        auto* pClass = Mono::mono_class_from_name(image, method_desc->namespace_name, method_desc->class_name);
        Mono::mono_method_desc_free(method_desc);

        Mono::MonoObject* pPlayersCollection = nullptr;
        Mono::mono_get_static_field_value(
            pClass, 
            0x0400111C, // ENTITY_COLLECTION::HUMANS
            &pPlayersCollection
        );

        // dictionary
        auto* pField = Mono::mono_class_get_field(
            Mono::mono_object_get_class(pPlayersCollection),
            0x04002FBB // KeyedCollection::dict
        );

        Mono::mono_field_get_value(pPlayersCollection, pField, &players);

        Mono::mono_dump_class(Mono::mono_object_get_class((Mono::MonoObject*)players));
	}
	
    return players;
}

void BrokeProtocol::fire()
{
    STATIC_METHOD("BrokeProtocol.Entities.ShPlayer:Fire(int)", true);
	
    auto* player = BrokeProtocol::GetLocalPlayer();

    void* args[1]{&player->current_weapon()->index};

    Mono::mono_runtime_invoke(pMethod, player, args, nullptr);
}

void BrokeProtocol::SendToServer(PacketFlags flags, BrokeProtocol::SvPacket packet, Mono::MonoArray* array)
{
    STATIC_METHOD("BrokeProtocol.Managers.ClManager:SendToServer(string)", true);

    Mono::MonoObject* exception = nullptr;

    void* args[3] {&flags,&packet,array};
    Mono::mono_runtime_invoke(pMethod, BrokeProtocol::GetLocalPlayer()->clPlayer->clManager, args, &exception);

    if (exception != nullptr)
    {
        DEBUG_LOG("[BP] CANNOT SEND TO SERVER");
        Mono::mono_print_unhandled_exception(exception);
    }
}

void BrokeProtocol::show_local_message(char*text)
{
    STATIC_METHOD("BrokeProtocol.Managers.ClManager:ShowGameMessage(string)", true);
	
    void* params[1] {Mono::create_csharp_string(text)};
	
    Mono::MonoObject* exception = nullptr;
	
    Mono::mono_runtime_invoke(pMethod, BrokeProtocol::GetLocalPlayer()->clPlayer->clManager, params, &exception);

	if(exception!=nullptr)
	{
        DEBUG_LOG("NIGGER ERROR");
        Mono::mono_print_unhandled_exception(exception);
	}
}

void BrokeProtocol::send_global_chat(char* text)
{
    auto* ptr = Mono::create_csharp_string(text);

    Mono::MonoArray* theArray = Mono::mono_array_new(Mono::mono_get_root_domain(), Mono::get_object_class(), 1);
    theArray->vector[0] = (__int64)ptr;

    BrokeProtocol::SendToServer(PacketFlags::Reliable, SvPacket::GlobalMessage, theArray);
}

void BrokeProtocol::jump()
{
    STATIC_METHOD("BrokeProtocol.Entities.ShPlayer:Jump()", true);
	
    Mono::mono_runtime_invoke(pMethod, BrokeProtocol::GetLocalPlayer(), nullptr, nullptr);
}
