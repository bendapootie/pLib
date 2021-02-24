#pragma once

//
//	You must define one of the following for a given game project configuration:
//	DEBUG_BUILD - for debugging; unoptimized build; dev warnings, errors, assertions and debug spew enabled
//	RELEASE_BUILD - close to the shipping game; optimized build; dev warnings, errors, assertions and debug spew still enabled
//

//-----------------------------------------------------------------------------
enum class BuildConfiguration {
	Debug,
	Release
};

enum class BuildPlatform {
	Win32,
	Win64
};

// Check for "_DEBUG" or "Debug_BUILD" which allows projects to set
// "$(ConfigurationName)_BUILD" in their Preprocessor Definitions.  That
// allows the project to use the same string across all configurations instead
// of relying on people to individually set a unique string per configuration.
//
// Note: Use the following syntax to conditionally compile a section of code...
// This is less error prone and clearer than the traditional "#ifdef DEBUG"
//#if BUILD_CONFIGURATION == BuildConfiguration::Release
//	... code here ...
//#endif
#if defined Debug_BUILD
#undef Debug_BUILD
#define DEBUG_BUILD		1
const BuildConfiguration BUILD_CONFIGURATION = BuildConfiguration::Debug;
#elif defined Release_BUILD
#undef Release_BUILD
#define RELEASE_BUILD	1
const BuildConfiguration BUILD_CONFIGURATION = BuildConfiguration::Release;
#else // unknown build configuration
#error unknown build configuration; expected to be one of: _DEBUG, NDEBUG, Debug_BUILD, or Release_BUILD
#endif // build configuration

//-----------------------------------------------------------------------------
// Target platform defines
// Note: Use the following syntax to conditionally compile a section of code...
//#if BUILD_PLATFORM == BuildPlatform::Win64
//	... code here ...
//#endif
#if defined PLATFORM_Win32
#undef PLATFORM_Win32		// don't use the mixed case version
#define PLATFORM_WIN_32		1
#define PLATFORM_WIN_ANY	1
const BuildPlatform BUILD_PLATFORM = BuildPlatform::Win32;
#elif defined PLATFORM_x64
#undef PLATFORM_x64			// don't use the mixed case version
#define PLATFORM_WIN_64		1
#define PLATFORM_WIN_ANY	1
const BuildPlatform BUILD_PLATFORM = BuildPlatform::Win64;
#else
#error unknown platform; must be one of: PLATFORM_Win32, PLATFORM_x64
#endif


//-----------------------------------------------------------------------------
// Returns the build configuration
inline constexpr BuildConfiguration GetBuildConfiguration()
{
	return BUILD_CONFIGURATION;
}

//-----------------------------------------------------------------------------
// Returns true if this is a Debug build
inline constexpr bool IsBuildDebug()
{
	return GetBuildConfiguration() == BuildConfiguration::Debug;
}

//-----------------------------------------------------------------------------
// Returns true if this is a Release build
inline constexpr bool IsBuildRelease()
{
	return GetBuildConfiguration() == BuildConfiguration::Release;
}

//-----------------------------------------------------------------------------
// Returns the target platform
inline constexpr BuildPlatform GetTargetPlatform()
{
	return BUILD_PLATFORM;
}

//-----------------------------------------------------------------------------
// Returns true if we're on Win32
inline constexpr bool IsPlatformWin32()
{
	return GetTargetPlatform() == BuildPlatform::Win32;
}

//-----------------------------------------------------------------------------
// Returns true if we're on Win64
inline constexpr bool IsPlatformWin64()
{
	return GetTargetPlatform() == BuildPlatform::Win64;
}
