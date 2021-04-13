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

void BrokeProtocol::send_nigger()
{
    auto* image = Mono::mono_image_loaded("D:\\Steam\\steamapps\\common\\BROKE PROTOCOL\\BrokeProtocol_Data\\Managed\\Scripts.dll");
    auto* method_desc = Mono::mono_method_desc_new("BrokeProtocol.Managers.ClManager:SendToServer(int,int,object[])", true);

    auto* pClass = Mono::mono_class_from_name(image, method_desc->namespace_name, method_desc->class_name);
    

    DEBUG_LOG("CLASS: " << pClass);

    auto* method = Mono::mono_class_get_method_from_name(pClass, "SendToServer", -1);

    DEBUG_LOG("METHOD: " << method);

    auto* player = BrokeProtocol::GetLocalPlayer();

    DEBUG_LOG("PLAYER: " << player);

    void* params[3];

    params[0] = new int(0x1);
    params[1] = new int(0x12);
    params[2] = new int[40];
	
    void* excepion = nullptr;
	
    Mono::mono_thread_attach(Mono::mono_get_root_domain());
    Mono::mono_runtime_invoke(method, player->clPlayer->clManager, params, &excepion);

	if(excepion!=nullptr)
	{
        DEBUG_LOG("NIGGER ERROR");
        Mono::mono_print_unhandled_exception(excepion);
	}

    Mono::mono_method_desc_free(method_desc);
}

void BrokeProtocol::send_slave_ff()
{
    auto* image = Mono::mono_image_loaded("D:\\Steam\\steamapps\\common\\BROKE PROTOCOL\\BrokeProtocol_Data\\Managed\\Scripts.dll");
    auto* method_desc = Mono::mono_method_desc_new("BrokeProtocol.Entities.SvPlayer:SvGlobalChatMessage(string)", true);

    auto* pClass = Mono::mono_class_from_name(image, method_desc->namespace_name, method_desc->class_name);

    DEBUG_LOG("CLASS: " << pClass);

    auto* method = Mono::mono_class_get_method_from_name(pClass, method_desc->method_name, -1);

    DEBUG_LOG("METHOD: " << method);

    void* params[1];

    params[0] = Mono::create_csharp_string((char*)("FEFE GAY!!!"));

    void* excepion = nullptr;
    auto* player = BrokeProtocol::GetLocalPlayer();
    Mono::mono_thread_attach(Mono::mono_get_root_domain());
    Mono::mono_runtime_invoke(method, player->svPlayer, params, &excepion);

    if (excepion != nullptr)
    {
        DEBUG_LOG("NIGGER ERROR");
        Mono::mono_print_unhandled_exception(excepion);
    }
}
