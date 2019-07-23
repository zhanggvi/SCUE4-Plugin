///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//		Copyright 2016 (C) Bruno Xavier B. Leite
//////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SCUE4.h"
#include "SCUE4PrivatePCH.h"
#include "Interfaces/IPluginManager.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void USafeGameInstance::HideGameGuardConsole(bool Set) {
	this->HideGameGuard = Set;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

USCUE4Settings::USCUE4Settings(const FObjectInitializer& OBJ) : Super(OBJ) {
	KeyGeneratorPath = FPaths::Combine(*IPluginManager::Get().FindPlugin(TEXT("SCUE4"))->GetBaseDir(),TEXT("Source/ThirdParty/"),TEXT("SCUE4_Key-Generator.exe"));
	//
	IllegalKeywords.AddUnique(FString(TEXT("spy")));
	IllegalKeywords.AddUnique(FString(TEXT("autohotkey")));
	IllegalKeywords.AddUnique(FString(TEXT("artmoney")));
	IllegalKeywords.AddUnique(FString(TEXT("injector")));
	IllegalKeywords.AddUnique(FString(TEXT("cheat")));
	IllegalKeywords.AddUnique(FString(TEXT("hack")));
	IllegalKeywords.AddUnique(FString(TEXT("crack")));
	IllegalKeywords.AddUnique(FString(TEXT("ccdebug")));
	IllegalKeywords.AddUnique(FString(TEXT("debugger")));
	IllegalKeywords.AddUnique(FString(TEXT("decompile")));
	IllegalKeywords.AddUnique(FString(TEXT("dotpeek")));
	IllegalKeywords.AddUnique(FString(TEXT("eclipse")));
	IllegalKeywords.AddUnique(FString(TEXT("eztest")));
	IllegalKeywords.AddUnique(FString(TEXT("fusion")));
	IllegalKeywords.AddUnique(FString(TEXT("codeview")));
	IllegalKeywords.AddUnique(FString(TEXT("haxplorer")));
	IllegalKeywords.AddUnique(FString(TEXT("hookshark")));
	IllegalKeywords.AddUnique(FString(TEXT("memory editor")));
	IllegalKeywords.AddUnique(FString(TEXT("monodevelop")));
	IllegalKeywords.AddUnique(FString(TEXT("ollydbg")));
	IllegalKeywords.AddUnique(FString(TEXT("reflector")));
	IllegalKeywords.AddUnique(FString(TEXT("slickedit")));
	IllegalKeywords.AddUnique(FString(TEXT("totalview")));
	IllegalKeywords.AddUnique(FString(TEXT("trainer")));
	IllegalKeywords.AddUnique(FString(TEXT("windbg")));
	IllegalKeywords.AddUnique(FString(TEXT("xdebug")));
	IllegalKeywords.AddUnique(FString(TEXT("x64dbg")));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
//
BOOL CALLBACK ScanProcesses(HWND Hwnd, LPARAM Param) {
	const auto &Settings = GetMutableDefault<USCUE4Settings>();
	//
	char TBuffer[512];
	int TXT = GetWindowTextA(Hwnd,TBuffer,sizeof(TBuffer));
	FString FST = FString(ANSI_TO_TCHAR(TBuffer)).ToLower();
	//
	TCHAR LPS[512];
	GetClassNameW(Hwnd,LPS,512);
	FString FSN = FString(LPS).ToLower();
	//
	for (auto SC : Settings->IllegalKeywords) {
		if (FSN.Contains(SC)) {*(HWND*)Param = Hwnd; return FALSE;}
		if (TXT && FST.Contains(SC) && !FST.Contains(TEXT("internet")) && !FST.Contains(TEXT("edge")) && !FST.Contains(TEXT("chrome"))
		&& !FST.Contains(TEXT("firefox")) && !FST.Contains(TEXT("opera")) && !FST.Contains(TEXT("safari")) && !FST.Contains(TEXT("torch")))
	{*(HWND*)Param = Hwnd; return FALSE;}}
	//
	return TRUE;
}///
//
void FSCUE4_Enumerate() {
	HWND Hwnd = NULL;
	if (!EnumWindows(ScanProcesses,reinterpret_cast<LPARAM>(&Hwnd))) {
	  #if UE_BUILD_SHIPPING
		char TBuffer[512];
		int TXT = GetWindowTextA(Hwnd,TBuffer,sizeof(TBuffer));
		int msgboxID = MessageBox( NULL,
			(LPCWSTR)L"Running application conflict detected; Game will close;\nPlease close conflicting software before playing.",
			(LPCWSTR)TBuffer,
			MB_ICONWARNING | MB_OK | MB_DEFBUTTON1
		); FGenericPlatformMisc::RequestExit(false);
	  #endif
	}/// else {CloseHandle(Hwnd);}
}///
//
#include "Windows/HideWindowsPlatformTypes.h"
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////