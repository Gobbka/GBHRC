#include "BrokeProtocol.h"
#include "../../includes/win.h"
#include "../../includes/logger.h"
#include "Mono/Mono.h"
#include "Mono/Images/Script/ScriptImage.h"
#include "Enum/Tokens.h"

using namespace Collections;

#define STATIC_METHOD(name,inc_namespace) static Mono::MonoMethod* pMethod = Mono::ScriptImage::mono_get_method_from_name(name, inc_namespace)

BrokeProtocol::Structs::MainCamera* BrokeProtocol::get_camera()
{
    Structs::MainCamera* camera = nullptr;
	if(camera==nullptr)
	{
        auto* mono_context = Mono::Context::get_context();
        auto* pclass = mono_context->mono_class_from_name(mono_context->get_script_image(), "BrokeProtocol.Client.UI", "MainCamera");
        auto* parent = mono_context->mono_class_get_parent(pclass);
        mono_context->mono_get_static_field_value(
            parent,
            BPTokens::MonoBehaviourSingleton_CKMGNJHFDLL, // MonoBehaviourSingleton::CKMGNJHFDLL
            &camera
        );
	}

    return camera;
}

BrokeProtocol::Structs::Evaluator* BrokeProtocol::get_evaluator()
{
    static size_t pointer;

    if (pointer == 0)
    {
        auto* const unity_player = GetModuleHandle(L"UnityPlayer.dll");
    	
        size_t step = *(size_t*)((size_t)unity_player + 0X1983398);
        step = *(size_t*)(step + 0X0);
        step = *(size_t*)(step + 0X10);
        pointer = step;
    }
    auto buffer = pointer;
    buffer = *(size_t*)(buffer + 0X198);
    buffer = *(size_t*)(buffer + 0x340);

    
	
    return (Structs::Evaluator*)buffer;
}

BrokeProtocol::Structs::GlobalTypes* BrokeProtocol::get_global_types()
{
    return get_evaluator()->GlobalTypes;
}

BrokeProtocol::Managers::ShManager* BrokeProtocol::get_manager()
{
    return get_global_types()->manager;
}

BrokeProtocol::Players::ShPlayer* BrokeProtocol::GetLocalPlayer()
{
    return get_global_types()->player;
}

KeyedCollection<BrokeProtocol::Players::ShPlayer*>* BrokeProtocol::GetPlayersCollection()
{
    static KeyedCollection<Players::ShPlayer*>* players;

	if(players==nullptr)
	{
        auto* mono_context = Mono::Context::get_context();
        auto* image = mono_context->get_script_image();
        auto* method_desc = mono_context->mono_method_desc_new("BrokeProtocol.Collections.EntityCollections:n()", true);

        auto* pClass = mono_context->mono_class_from_name(image, method_desc->namespace_name, method_desc->class_name);
        mono_context->mono_method_desc_free(method_desc);

        mono_context->mono_get_static_field_value(
            pClass, 
            BPTokens::EntityCollection_HUMANS, // ENTITY_COLLECTION::HUMANS
            &players
        );
	}
	
    return players;
}

void BrokeProtocol::fire()
{
    STATIC_METHOD("BrokeProtocol.Entities.ShPlayer:Fire(int)", true);
	
    auto* player = BrokeProtocol::GetLocalPlayer();

    void* args[1]{&player->current_weapon()->index};

    Mono::Context::get_context()->mono_runtime_invoke(pMethod, player, args, nullptr);
}

void BrokeProtocol::SendToServer(PacketFlags flags, BrokeProtocol::SvPacket packet, Mono::MonoArray* array)
{
    STATIC_METHOD("BrokeProtocol.Managers.ClManager:SendToServer(string)", true);

    Mono::MonoObject* exception = nullptr;

    void* args[3] {&flags,&packet,array};
    Mono::Context::get_context()->mono_runtime_invoke(pMethod, BrokeProtocol::GetLocalPlayer()->clPlayer->clManager, args, &exception);

    if (exception != nullptr)
    {
        DEBUG_LOG("[BP] CANNOT SEND TO SERVER");
    }
}

void BrokeProtocol::show_local_message(char*text)
{
	
    STATIC_METHOD("BrokeProtocol.Managers.ClManager:ShowGameMessage(string)", true);

    auto* mono_context = Mono::Context::get_context();
	
    void* params[1] { mono_context->create_csharp_string(text)};
	
    Mono::MonoObject* exception = nullptr;
	
    mono_context->mono_runtime_invoke(pMethod, BrokeProtocol::get_global_types()->clManager, params, &exception);

	if(exception!=nullptr)
	{
        DEBUG_LOG("NIGGER ERROR");
	}
}

void BrokeProtocol::send_global_chat(char* text)
{
    auto* mono_context = Mono::Context::get_context();
    auto* ptr = mono_context->create_csharp_string(text);

    Mono::MonoArray* theArray = mono_context->mono_array_new(mono_context->mono_get_root_domain(), mono_context->get_object_class(), 1);
    theArray->vector[0] = (__int64)ptr;

    BrokeProtocol::SendToServer(PacketFlags::Reliable, SvPacket::GlobalMessage, theArray);
}

void BrokeProtocol::ShowTextMenu(float xMin, float yMin, float xMax, float yMax,const char* title,const char* text)
{
    STATIC_METHOD("BrokeProtocol.Managers.ClManager:ShowTextPanel()",true);

    auto* mono_context = Mono::Context::get_context();
	
    auto* text_str = mono_context->create_csharp_string((char*)text);

    void* args[]{ text_str };

    DEBUG_LOG("METHOD:" << pMethod);
    DEBUG_LOG("PISKA: " << BrokeProtocol::GetLocalPlayer()->clPlayer->clManager);

    Mono::MonoObject* exc;
	
    mono_context->mono_runtime_invoke(pMethod, BrokeProtocol::get_manager()->clManager,args,&exc);

	if(exc!=nullptr)
	{
        DEBUG_LOG("NIGGER ERROR");
	}
}

void BrokeProtocol::ShowTextPanel(const char* text)
{
    STATIC_METHOD("BrokeProtocol.Managers.ClManager:ShowTextPanel()", true);
    auto* mono_context = Mono::Context::get_context();
    void* args[]{ mono_context->create_csharp_string((char*)text) };

    mono_context->mono_runtime_invoke(pMethod, BrokeProtocol::get_global_types()->clManager, args, nullptr);
}
