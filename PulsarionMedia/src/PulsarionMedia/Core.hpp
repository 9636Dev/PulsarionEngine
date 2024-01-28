#pragma once

#include <PulsarionCore/Core.hpp>
#include <PulsarionCore/Assert.hpp>

#ifdef PULSARION_MEDIA_BUILD_DLL
	#define PULSARION_MEDIA_API PULSARION_DLL_EXPORT
#else
	#define PULSARION_MEDIA_API PULSARION_DLL_IMPORT
#endif

namespace Pulsarion::Media
{

}
