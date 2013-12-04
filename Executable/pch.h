#pragma once

// Windows headers
#include <sdkddkver.h>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN // ������� ���� ����
#include <windows.h>
#include <Shobjidl.h>
#include <comdef.h>
#include <atlbase.h>

// C++ headers
#include <functional>
#include <fstream>
#include <iomanip>

// ����� ���
#include <ErrorReporter.h>
#include <RAII.h>