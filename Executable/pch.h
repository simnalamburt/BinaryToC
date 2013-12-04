#pragma once

// Windows headers
#include <sdkddkver.h>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN // 쓸모없는 내용 제외
#include <windows.h>
#include <Shobjidl.h>
#include <comdef.h>
#include <atlbase.h>

// C++ headers
#include <functional>
#include <fstream>
#include <iomanip>

// 사용자 헤더
#include <ErrorReporter.h>
#include <RAII.h>