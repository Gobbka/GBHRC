#include "BrokeProtocol.h"
#include "../../includes/win.h"
#include "../../includes/logger.h"
#include "Mono/Mono.h"

ShManager* BrokeProtocol::get_manager()
{
    static ShManager* manager;

	if(manager==nullptr)
	{
        auto* const unity_player = GetModuleHandle(L"UnityPlayer.dll");
        manager = (ShManager*)*(size_t*)(*(size_t*)(*(size_t*)(*(size_t*)((size_t)unity_player + 0X19DD788) + 0X218) + 0X60) + 0X18);
	}
	
    return reinterpret_cast<ShManager*>(manager);
}

ShPlayer* BrokeProtocol::GetLocalPlayer()
{
    return get_manager()->clManager->myPlayer;
}

void* BrokeProtocol::GetPlayersCollection()
{
    auto* image = Mono::get_script_image();
    auto* method_desc = Mono::mono_method_desc_new("BrokeProtocol.Collections.EntityCollections:n()", true);
	
    auto* pClass = Mono::mono_class_from_name(image, method_desc->namespace_name, method_desc->class_name);
    Mono::mono_method_desc_free(method_desc);
    DEBUG_LOG("CLASS: " << pClass);
    auto* vTable = (Mono::MonoVTable*)Mono::mono_class_vtable(Mono::mono_get_root_domain(),pClass);

    auto* collectionClass = Mono::mono_object_get_class((Mono::MonoObject*)vTable);


    void* pointer = NULL;
    Mono::MonoClassField* field = NULL;

    while ((field = Mono::mono_class_get_fields(collectionClass, &pointer)))
    {
    	if(strcmp("<JFOPDLAIMGM>k__BackingField", mono_field_get_name(field))!=0)
    	{
            DEBUG_LOG("0x" << std::hex << mono_field_get_offset(field) << " : " << mono_field_get_name(field));

            Mono::MonoObject* humans = nullptr;
            Mono::mono_field_static_get_value(vTable, field, &humans);

            auto* collection = Mono::mono_object_get_class((Mono::MonoObject*)humans);

            auto* pField = Mono::mono_class_get_field(
                collection,
                0x04002FB6
            );

            DEBUG_LOG("FIELD: " << Mono::mono_field_get_name(pField));

            int nigger_count = -1;
            Mono::mono_field_get_value(humans, pField, &nigger_count);

            DEBUG_LOG("COUNT: " << nigger_count);
            DEBUG_LOG("=========================");
    	}
    }

    return nullptr;
    //=============================
	
    auto* pField = Mono::mono_class_get_field(
        Mono::mono_object_get_class((Mono::MonoObject*)vTable),
        0x0400103E
    );

    Mono::MonoObject* humans = nullptr;
    Mono::mono_field_static_get_value(vTable, pField, &humans);

    auto* collection = Mono::mono_object_get_class((Mono::MonoObject*)humans);

    pField = Mono::mono_class_get_field(
        collection,
        0x04002FBB
    );

    DEBUG_LOG("FIELD: " << Mono::mono_field_get_name(pField));
	
    int nigger_count = -1;
    Mono::mono_field_get_value(humans, pField, &nigger_count);

    DEBUG_LOG("COUNT: " << nigger_count);
	
    Mono::mono_dump_class(
        collection
    );

    return nullptr;
}

void BrokeProtocol::fire()
{
    auto* image = Mono::get_script_image();
    auto* method_desc = Mono::mono_method_desc_new("BrokeProtocol.Entities.ShPlayer:Fire(int)", true);

    auto* pClass = Mono::mono_class_from_name(image, method_desc->namespace_name, method_desc->class_name);
    auto* method = Mono::mono_class_get_method_from_name(pClass, method_desc->method_name, -1);
    auto* player = BrokeProtocol::GetLocalPlayer();

    void* args[1];
    args[0] = &player->current_weapon()->index;

    Mono::mono_runtime_invoke(method, player, args, nullptr);
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
