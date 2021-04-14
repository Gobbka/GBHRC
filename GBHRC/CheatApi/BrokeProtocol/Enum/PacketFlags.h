#pragma once

namespace BrokeProtocol
{
	enum class PacketFlags
	{
		// Token: 0x04000002 RID: 2
		None = 0,
		// Token: 0x04000003 RID: 3
		Reliable = 1,
		// Token: 0x04000004 RID: 4
		Unsequenced = 2,
		// Token: 0x04000005 RID: 5
		NoAllocate = 4,
		// Token: 0x04000006 RID: 6
		UnreliableFragmented = 8,
		// Token: 0x04000007 RID: 7
		Instant = 16,
		// Token: 0x04000008 RID: 8
		Unthrottled = 32,
		// Token: 0x04000009 RID: 9
		Sent = 256
	};
}
