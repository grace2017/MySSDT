/************************************************************************/
/*
win7 x32 自建调试体系

0环3环调用框架使用IDT表索引：35
*/
/************************************************************************/

#include <ntddk.h>

#include "kernel.h"
#include "IDT.h"
#include "SSDT.h"

PKSYSTEM_SERVICE_TABLE pSystemServiceTable;

ULONG demo(IN ULONG a, IN ULONG b)
{
	DbgPrint("%d \n", a + b);

	return a + b;
}

VOID DriverUnload(PDRIVER_OBJECT pDriverObj)
{
	UNREFERENCED_PARAMETER(pDriverObj);

	FreeSystemServiceTable(pSystemServiceTable);

	DbgPrint("驱动已卸载 \n");
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObj, PUNICODE_STRING pRegistryString)
{
	NTSTATUS status = STATUS_SUCCESS;

	UNREFERENCED_PARAMETER(pRegistryString);

	status = CreateSystemServiceTable(&pSystemServiceTable);
	if (!NT_SUCCESS(status)) {
		DbgPrint("%s(%d): CreateSystemServiceTable failed.", __FILE__, __LINE__);

		return status;
	} else {
		DbgPrint("SystemServiceTable地址：%X \n", pSystemServiceTable);
	}

	// 向IDT表中增加函数
	AddFun2SystemServiceTable(pSystemServiceTable, (ULONG)demo, 2);								//0

	SetIDTEntry(35, (ULONG)YKiSystemService);


	pDriverObj->DriverUnload = DriverUnload;

	return status;
}