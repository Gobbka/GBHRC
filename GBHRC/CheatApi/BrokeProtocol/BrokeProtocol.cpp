#include "BrokeProtocol.h"
#include "../../includes/win.h"
#include "../../includes/logger.h"
#include "Mono/Mono.h"

ShPlayer* BrokeProtocol::GetLocalPlayer()
{
	auto* const unity_player = GetModuleHandle(L"UnityPlayer.dll");
	auto ptr = *(size_t*)(*(size_t*)(*(size_t*)(*(size_t*)((size_t)unity_player + 0x19E0D60) + 0x80) + 0x3C8) + 0x108);
	return reinterpret_cast<ShPlayer*>(ptr);
}

void* BrokeProtocol::GetPlayersCollection()
{
    auto* image = Mono::mono_image_loaded("D:\\Steam\\steamapps\\common\\BROKE PROTOCOL\\BrokeProtocol_Data\\Managed\\Scripts.dll");
    auto* method_desc = Mono::mono_method_desc_new("BrokeProtocol.Collections.EntityCollections:n()", true);
	
    auto* pClass = Mono::mono_class_from_name(image, method_desc->namespace_name, method_desc->class_name);
    DEBUG_LOG("NIGGER FIELD");
    Mono::mono_method_desc_free(method_desc);
    DEBUG_LOG("CLASS: " << pClass);
    auto* pField = Mono::mono_class_get_field(pClass, 0x170000F3);
    DEBUG_LOG("FIELD: " << pField);

    return nullptr;
}

void BrokeProtocol::fire()
{
	
}

void BrokeProtocol::SendToServer(PacketFlags flags, BrokeProtocol::SvPacket packet, Mono::MonoArray* array)
{
    auto* image = Mono::get_script_image();
    auto* method_desc = Mono::mono_method_desc_new("BrokeProtocol.Managers.ClManager:SendToServer(string)", true);

    auto* pClass = Mono::mono_class_from_name(image, method_desc->namespace_name, method_desc->class_name);
    auto* method = Mono::mono_class_get_method_from_name(pClass, method_desc->method_name, -1);

    Mono::mono_method_desc_free(method_desc);

    Mono::MonoObject* exception = nullptr;

    void* args[3];

    args[0] = &flags;
    args[1] = &packet;
    args[2] = array;

    Mono::mono_runtime_invoke(method, BrokeProtocol::GetLocalPlayer()->clPlayer->clManager, args, &exception);

    if (exception != nullptr)
    {
        DEBUG_LOG("[BP] CANNOT SEND TO SERVER");
        Mono::mono_print_unhandled_exception(exception);
    }
}

void BrokeProtocol::show_local_message(char*text)
{
    auto* image = Mono::get_script_image();
    auto* method_desc = Mono::mono_method_desc_new("BrokeProtocol.Managers.ClManager:ShowGameMessage(string)", true);

    auto* pClass = Mono::mono_class_from_name(image, method_desc->namespace_name, method_desc->class_name);

    auto* method = Mono::mono_class_get_method_from_name(pClass, method_desc->method_name, -1);

    void* params[1];
	
    params[0] = Mono::create_csharp_string(text);
	
    Mono::MonoObject* exception = nullptr;
	
    Mono::mono_runtime_invoke(method, BrokeProtocol::GetLocalPlayer()->clPlayer->clManager, params, &exception);

	if(exception!=nullptr)
	{
        DEBUG_LOG("NIGGER ERROR");
        Mono::mono_print_unhandled_exception(exception);
	}

    Mono::mono_method_desc_free(method_desc);
}

void BrokeProtocol::send_global_chat(char* text)
{
    auto* ptr = Mono::create_csharp_string(text);

    Mono::MonoArray* theArray = Mono::mono_array_new(Mono::mono_get_root_domain(), Mono::get_object_class(), 1);
    theArray->vector[0] = (__int64)ptr;

    BrokeProtocol::SendToServer(PacketFlags::Reliable, SvPacket::GlobalMessage, theArray);
}
