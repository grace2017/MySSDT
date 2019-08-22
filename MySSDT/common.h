#ifndef __COMMON_H_
#define __COMMON_H_

#include <ntddk.h>

#ifdef __cplusplus
extern "C" {
#endif

	/*
	关闭页保护
	*/
	VOID PageProtectOff();

	/*
	开启页保护
	*/
	void PageProtectOn();

	/*
	一次性修改8字节内存
	*/
	VOID Hook8b(IN ULONG hookAddr, IN PUCHAR hookBytesArr, OUT PUCHAR oldCode);

	VOID Int3();

#ifdef __cplusplus
}
#endif

#endif
