#pragma once

//-----------------------------------------------------------------------------
// Standard Headers
//-----------------------------------------------------------------------------
#include <stdarg.h>		// for va_args used by Error
#include <math.h>		// for math functions, ie. abs

//-----------------------------------------------------------------------------
// Config / Error headers
//-----------------------------------------------------------------------------
#include "BuildConfig.h"
#include "Error.h"

//-----------------------------------------------------------------------------
// Windows Specific headers
//
// TODO: Get all platform specific headers out of pLib.h!
//-----------------------------------------------------------------------------
#if PLATFORM_WIN_ANY
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#endif

//-----------------------------------------------------------------------------
// Types
//-----------------------------------------------------------------------------
#include "Types\Types.h"

//-----------------------------------------------------------------------------
// Util
//-----------------------------------------------------------------------------
#include "Util\Timer.h"
#include "Util\PImpl.h"
#include "Util\Random.h"

//-----------------------------------------------------------------------------
// Threads
//-----------------------------------------------------------------------------
#include "Threads\CriticalSection.h"
#include "Threads\Mutex.h"
#include "Threads\ThreadSignal.h"
#include "Threads\Thread.h"

//-----------------------------------------------------------------------------
// Math
//-----------------------------------------------------------------------------
#include "Math\Constants.h"
#include "Math\Math.h"
#include "Math\Point.h"
#include "Math\Quaternion.h"
#include "Math\Vector.h"
#include "Math\Matrix.h"
#include "Math\Transform.h"
#include "Math\Util.h"

//-----------------------------------------------------------------------------
// Containers
//-----------------------------------------------------------------------------
#include "Containers\pArray.h"
#include "Containers\pList.h"
#include "Containers\pStaticList.h"
#include "Containers\pStaticString.h"
#include "Containers\MTLinkedList.h"
#include "Containers\pCircularQueue.h"
#include "Containers\pMap.h"

//-----------------------------------------------------------------------------
// Event
//-----------------------------------------------------------------------------
#include "Event\EventBase.h"
#include "Event\EventListener.h"
#include "Event\EventManager.h"
