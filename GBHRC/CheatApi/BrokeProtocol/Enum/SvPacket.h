#pragma once

namespace BrokeProtocol {
	enum class SvPacket
	{
		// Token: 0x04000320 RID: 800
		Ready,
		// Token: 0x04000321 RID: 801
		Cache,
		// Token: 0x04000322 RID: 802
		ResetPacketCounter,
		// Token: 0x04000323 RID: 803
		Register,
		// Token: 0x04000324 RID: 804
		Login,
		// Token: 0x04000325 RID: 805
		Loaded,
		// Token: 0x04000326 RID: 806
		TransferView,
		// Token: 0x04000327 RID: 807
		TransferSearch,
		// Token: 0x04000328 RID: 808
		TransferShop,
		// Token: 0x04000329 RID: 809
		TransferTrade,
		// Token: 0x0400032A RID: 810
		View,
		// Token: 0x0400032B RID: 811
		Rob,
		// Token: 0x0400032C RID: 812
		StopInventory,
		// Token: 0x0400032D RID: 813
		Drop,
		// Token: 0x0400032E RID: 814
		TradeRequest,
		// Token: 0x0400032F RID: 815
		FinalizeTrade,
		// Token: 0x04000330 RID: 816
		ConfirmTrade,
		// Token: 0x04000331 RID: 817
		GetItemValue,
		// Token: 0x04000332 RID: 818
		Reload,
		// Token: 0x04000333 RID: 819
		Underbarrel,
		// Token: 0x04000334 RID: 820
		MountPrimary,
		// Token: 0x04000335 RID: 821
		MountBack,
		// Token: 0x04000336 RID: 822
		GetEntityValue,
		// Token: 0x04000337 RID: 823
		BuyTransport,
		// Token: 0x04000338 RID: 824
		BuyApartment,
		// Token: 0x04000339 RID: 825
		SellApartment,
		// Token: 0x0400033A RID: 826
		ShowCrimes,
		// Token: 0x0400033B RID: 827
		ShowHealth,
		// Token: 0x0400033C RID: 828
		Search,
		// Token: 0x0400033D RID: 829
		Shop,
		// Token: 0x0400033E RID: 830
		GetJob,
		// Token: 0x0400033F RID: 831
		QuitJob,
		// Token: 0x04000340 RID: 832
		BuyFurniture,
		// Token: 0x04000341 RID: 833
		Dismount,
		// Token: 0x04000342 RID: 834
		Free,
		// Token: 0x04000343 RID: 835
		TriggerEvent,
		// Token: 0x04000344 RID: 836
		EventAction,
		// Token: 0x04000345 RID: 837
		SpecialAction,
		// Token: 0x04000346 RID: 838
		EmployeeAction,
		// Token: 0x04000347 RID: 839
		SelfAction,
		// Token: 0x04000348 RID: 840
		UpdateInput,
		// Token: 0x04000349 RID: 841
		UpdatePlayer,
		// Token: 0x0400034A RID: 842
		UpdatePhysical,
		// Token: 0x0400034B RID: 843
		UpdateRotation,
		// Token: 0x0400034C RID: 844
		Jump,
		// Token: 0x0400034D RID: 845
		Embark,
		// Token: 0x0400034E RID: 846
		Disembark,
		// Token: 0x0400034F RID: 847
		JailCriminal,
		// Token: 0x04000350 RID: 848
		GlobalMessage,
		// Token: 0x04000351 RID: 849
		LocalMessage,
		// Token: 0x04000352 RID: 850
		ProgressAction,
		// Token: 0x04000353 RID: 851
		ProcessAction,
		// Token: 0x04000354 RID: 852
		SetSiren,
		// Token: 0x04000355 RID: 853
		TrySetEquipable,
		// Token: 0x04000356 RID: 854
		StartVote,
		// Token: 0x04000357 RID: 855
		VoteYes,
		// Token: 0x04000358 RID: 856
		VoteNo,
		// Token: 0x04000359 RID: 857
		DrugTest,
		// Token: 0x0400035A RID: 858
		KillSelf,
		// Token: 0x0400035B RID: 859
		Crouch,
		// Token: 0x0400035C RID: 860
		Collect,
		// Token: 0x0400035D RID: 861
		Consume,
		// Token: 0x0400035E RID: 862
		TimeScale,
		// Token: 0x0400035F RID: 863
		Kick,
		// Token: 0x04000360 RID: 864
		Ban,
		// Token: 0x04000361 RID: 865
		Restrain,
		// Token: 0x04000362 RID: 866
		Teleport,
		// Token: 0x04000363 RID: 867
		Summon,
		// Token: 0x04000364 RID: 868
		RemoveJob,
		// Token: 0x04000365 RID: 869
		StopServer,
		// Token: 0x04000366 RID: 870
		GodMode,
		// Token: 0x04000367 RID: 871
		Follower,
		// Token: 0x04000368 RID: 872
		Invite,
		// Token: 0x04000369 RID: 873
		KickOut,
		// Token: 0x0400036A RID: 874
		Point,
		// Token: 0x0400036B RID: 875
		Alert,
		// Token: 0x0400036C RID: 876
		SellFurniture,
		// Token: 0x0400036D RID: 877
		ServiceCall,
		// Token: 0x0400036E RID: 878
		SetWearable,
		// Token: 0x0400036F RID: 879
		Deploy,
		// Token: 0x04000370 RID: 880
		Help,
		// Token: 0x04000371 RID: 881
		SaveAll,
		// Token: 0x04000372 RID: 882
		Fire,
		// Token: 0x04000373 RID: 883
		RequestServerInfo,
		// Token: 0x04000374 RID: 884
		PlayerRecords,
		// Token: 0x04000375 RID: 885
		BanRecords,
		// Token: 0x04000376 RID: 886
		BanAccount,
		// Token: 0x04000377 RID: 887
		UnbanIP,
		// Token: 0x04000378 RID: 888
		DropEquipable,
		// Token: 0x04000379 RID: 889
		DropItem,
		// Token: 0x0400037A RID: 890
		Heal,
		// Token: 0x0400037B RID: 891
		ClearCrimes,
		// Token: 0x0400037C RID: 892
		Spectate,
		// Token: 0x0400037D RID: 893
		ParkInside,
		// Token: 0x0400037E RID: 894
		ParkOutside,
		// Token: 0x0400037F RID: 895
		CheckHitscan,
		// Token: 0x04000380 RID: 896
		CheckBallistic,
		// Token: 0x04000381 RID: 897
		HandsUp,
		// Token: 0x04000382 RID: 898
		Bind,
		// Token: 0x04000383 RID: 899
		Unbind,
		// Token: 0x04000384 RID: 900
		BindAttachment,
		// Token: 0x04000385 RID: 901
		UnbindAttachment,
		// Token: 0x04000386 RID: 902
		SetAttachment,
		// Token: 0x04000387 RID: 903
		UseBind,
		// Token: 0x04000388 RID: 904
		EnterDoor,
		// Token: 0x04000389 RID: 905
		Disarm,
		// Token: 0x0400038A RID: 906
		Initialized,
		// Token: 0x0400038B RID: 907
		TransportState,
		// Token: 0x0400038C RID: 908
		Apps,
		// Token: 0x0400038D RID: 909
		AppContacts,
		// Token: 0x0400038E RID: 910
		AppBlocked,
		// Token: 0x0400038F RID: 911
		AppCalls,
		// Token: 0x04000390 RID: 912
		AppInbox,
		// Token: 0x04000391 RID: 913
		AppServices,
		// Token: 0x04000392 RID: 914
		AppDeposit,
		// Token: 0x04000393 RID: 915
		AppWithdraw,
		// Token: 0x04000394 RID: 916
		AppMessage,
		// Token: 0x04000395 RID: 917
		AppAddContact,
		// Token: 0x04000396 RID: 918
		AppRemoveContact,
		// Token: 0x04000397 RID: 919
		AppAddBlocked,
		// Token: 0x04000398 RID: 920
		AppRemoveBlocked,
		// Token: 0x04000399 RID: 921
		AppAddMessage,
		// Token: 0x0400039A RID: 922
		ReadMessage,
		// Token: 0x0400039B RID: 923
		ReadAll,
		// Token: 0x0400039C RID: 924
		Call,
		// Token: 0x0400039D RID: 925
		CallAccept,
		// Token: 0x0400039E RID: 926
		CallReject,
		// Token: 0x0400039F RID: 927
		Deposit,
		// Token: 0x040003A0 RID: 928
		Withdraw,
		// Token: 0x040003A1 RID: 929
		VoiceChat,
		// Token: 0x040003A2 RID: 930
		OptionAction,
		// Token: 0x040003A3 RID: 931
		SubmitInput,
		// Token: 0x040003A4 RID: 932
		Ping,
		// Token: 0x040003A5 RID: 933
		PingAll,
		// Token: 0x040003A6 RID: 934
		SecurityPanel,
		// Token: 0x040003A7 RID: 935
		Max
	};
}