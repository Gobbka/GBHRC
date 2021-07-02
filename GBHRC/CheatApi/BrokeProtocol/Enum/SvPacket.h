#pragma once

namespace BrokeProtocol {
	enum class SvPacket
	{
		// Token: 0x0400037B RID: 891
		Ready,
		// Token: 0x0400037C RID: 892
		Cache,
		// Token: 0x0400037D RID: 893
		ResetPacketCounter,
		// Token: 0x0400037E RID: 894
		Register,
		// Token: 0x0400037F RID: 895
		Login,
		// Token: 0x04000380 RID: 896
		Loaded,
		// Token: 0x04000381 RID: 897
		TransferView,
		// Token: 0x04000382 RID: 898
		TransferSearch,
		// Token: 0x04000383 RID: 899
		TransferShop,
		// Token: 0x04000384 RID: 900
		TransferTrade,
		// Token: 0x04000385 RID: 901
		View,
		// Token: 0x04000386 RID: 902
		Rob,
		// Token: 0x04000387 RID: 903
		Drop,
		// Token: 0x04000388 RID: 904
		TradeRequest,
		// Token: 0x04000389 RID: 905
		FinalizeTrade,
		// Token: 0x0400038A RID: 906
		ConfirmTrade,
		// Token: 0x0400038B RID: 907
		GetItemValue,
		// Token: 0x0400038C RID: 908
		StopInventory,
		// Token: 0x0400038D RID: 909
		HackingProbe,
		// Token: 0x0400038E RID: 910
		HackingMark,
		// Token: 0x0400038F RID: 911
		HackingStop,
		// Token: 0x04000390 RID: 912
		Reload,
		// Token: 0x04000391 RID: 913
		Underbarrel,
		// Token: 0x04000392 RID: 914
		MountPrimary,
		// Token: 0x04000393 RID: 915
		MountBack,
		// Token: 0x04000394 RID: 916
		GetEntityValue,
		// Token: 0x04000395 RID: 917
		BuyTransport,
		// Token: 0x04000396 RID: 918
		BuyApartment,
		// Token: 0x04000397 RID: 919
		SellApartment,
		// Token: 0x04000398 RID: 920
		ShowCrimes,
		// Token: 0x04000399 RID: 921
		ShowHealth,
		// Token: 0x0400039A RID: 922
		Search,
		// Token: 0x0400039B RID: 923
		Shop,
		// Token: 0x0400039C RID: 924
		GetJob,
		// Token: 0x0400039D RID: 925
		QuitJob,
		// Token: 0x0400039E RID: 926
		BuyFurniture,
		// Token: 0x0400039F RID: 927
		Dismount,
		// Token: 0x040003A0 RID: 928
		Free,
		// Token: 0x040003A1 RID: 929
		TriggerEvent,
		// Token: 0x040003A2 RID: 930
		EventAction,
		// Token: 0x040003A3 RID: 931
		SpecialAction,
		// Token: 0x040003A4 RID: 932
		EmployeeAction,
		// Token: 0x040003A5 RID: 933
		SelfAction,
		// Token: 0x040003A6 RID: 934
		UpdateInput,
		// Token: 0x040003A7 RID: 935
		UpdatePlayer,
		// Token: 0x040003A8 RID: 936
		UpdatePhysical,
		// Token: 0x040003A9 RID: 937
		UpdateRotation,
		// Token: 0x040003AA RID: 938
		Jump,
		// Token: 0x040003AB RID: 939
		Embark,
		// Token: 0x040003AC RID: 940
		Disembark,
		// Token: 0x040003AD RID: 941
		JailCriminal,
		// Token: 0x040003AE RID: 942
		GlobalMessage,
		// Token: 0x040003AF RID: 943
		LocalMessage,
		// Token: 0x040003B0 RID: 944
		ProgressAction,
		// Token: 0x040003B1 RID: 945
		ProcessAction,
		// Token: 0x040003B2 RID: 946
		SetSiren,
		// Token: 0x040003B3 RID: 947
		TrySetEquipable,
		// Token: 0x040003B4 RID: 948
		StartVote,
		// Token: 0x040003B5 RID: 949
		VoteYes,
		// Token: 0x040003B6 RID: 950
		VoteNo,
		// Token: 0x040003B7 RID: 951
		DrugTest,
		// Token: 0x040003B8 RID: 952
		KillSelf,
		// Token: 0x040003B9 RID: 953
		Crouch,
		// Token: 0x040003BA RID: 954
		Collect,
		// Token: 0x040003BB RID: 955
		Consume,
		// Token: 0x040003BC RID: 956
		TimeScale,
		// Token: 0x040003BD RID: 957
		Kick,
		// Token: 0x040003BE RID: 958
		Ban,
		// Token: 0x040003BF RID: 959
		Restrain,
		// Token: 0x040003C0 RID: 960
		Teleport,
		// Token: 0x040003C1 RID: 961
		Summon,
		// Token: 0x040003C2 RID: 962
		RemoveJob,
		// Token: 0x040003C3 RID: 963
		StopServer,
		// Token: 0x040003C4 RID: 964
		GodMode,
		// Token: 0x040003C5 RID: 965
		Follower,
		// Token: 0x040003C6 RID: 966
		Invite,
		// Token: 0x040003C7 RID: 967
		KickOut,
		// Token: 0x040003C8 RID: 968
		Point,
		// Token: 0x040003C9 RID: 969
		Alert,
		// Token: 0x040003CA RID: 970
		SellFurniture,
		// Token: 0x040003CB RID: 971
		ServiceCall,
		// Token: 0x040003CC RID: 972
		SetWearable,
		// Token: 0x040003CD RID: 973
		Deploy,
		// Token: 0x040003CE RID: 974
		Help,
		// Token: 0x040003CF RID: 975
		SaveAll,
		// Token: 0x040003D0 RID: 976
		Fire,
		// Token: 0x040003D1 RID: 977
		RequestServerInfo,
		// Token: 0x040003D2 RID: 978
		PlayerRecords,
		// Token: 0x040003D3 RID: 979
		BanRecords,
		// Token: 0x040003D4 RID: 980
		BanAccount,
		// Token: 0x040003D5 RID: 981
		UnbanIP,
		// Token: 0x040003D6 RID: 982
		DropEquipable,
		// Token: 0x040003D7 RID: 983
		DropItem,
		// Token: 0x040003D8 RID: 984
		Heal,
		// Token: 0x040003D9 RID: 985
		ClearCrimes,
		// Token: 0x040003DA RID: 986
		Spectate,
		// Token: 0x040003DB RID: 987
		ParkInside,
		// Token: 0x040003DC RID: 988
		ParkOutside,
		// Token: 0x040003DD RID: 989
		CheckHitscan,
		// Token: 0x040003DE RID: 990
		CheckBallistic,
		// Token: 0x040003DF RID: 991
		HandsUp,
		// Token: 0x040003E0 RID: 992
		Bind,
		// Token: 0x040003E1 RID: 993
		Unbind,
		// Token: 0x040003E2 RID: 994
		BindAttachment,
		// Token: 0x040003E3 RID: 995
		UnbindAttachment,
		// Token: 0x040003E4 RID: 996
		SetAttachment,
		// Token: 0x040003E5 RID: 997
		UseBind,
		// Token: 0x040003E6 RID: 998
		EnterDoor,
		// Token: 0x040003E7 RID: 999
		Disarm,
		// Token: 0x040003E8 RID: 1000
		Initialized,
		// Token: 0x040003E9 RID: 1001
		TransportState,
		// Token: 0x040003EA RID: 1002
		Apps,
		// Token: 0x040003EB RID: 1003
		AppContacts,
		// Token: 0x040003EC RID: 1004
		AppBlocked,
		// Token: 0x040003ED RID: 1005
		AppCalls,
		// Token: 0x040003EE RID: 1006
		AppInbox,
		// Token: 0x040003EF RID: 1007
		AppServices,
		// Token: 0x040003F0 RID: 1008
		AppDeposit,
		// Token: 0x040003F1 RID: 1009
		AppWithdraw,
		// Token: 0x040003F2 RID: 1010
		AppMessage,
		// Token: 0x040003F3 RID: 1011
		AppAddContact,
		// Token: 0x040003F4 RID: 1012
		AppRemoveContact,
		// Token: 0x040003F5 RID: 1013
		AppAddBlocked,
		// Token: 0x040003F6 RID: 1014
		AppRemoveBlocked,
		// Token: 0x040003F7 RID: 1015
		AppAddMessage,
		// Token: 0x040003F8 RID: 1016
		ReadMessage,
		// Token: 0x040003F9 RID: 1017
		ReadAll,
		// Token: 0x040003FA RID: 1018
		Call,
		// Token: 0x040003FB RID: 1019
		CallAccept,
		// Token: 0x040003FC RID: 1020
		CallReject,
		// Token: 0x040003FD RID: 1021
		Deposit,
		// Token: 0x040003FE RID: 1022
		Withdraw,
		// Token: 0x040003FF RID: 1023
		VoiceChat,
		// Token: 0x04000400 RID: 1024
		OptionAction,
		// Token: 0x04000401 RID: 1025
		SubmitInput,
		// Token: 0x04000402 RID: 1026
		Ping,
		// Token: 0x04000403 RID: 1027
		PingAll,
		// Token: 0x04000404 RID: 1028
		SecurityPanel,
		// Token: 0x04000405 RID: 1029
		MenuClosed,
		// Token: 0x04000406 RID: 1030
		Max
	};
}