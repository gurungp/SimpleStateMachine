#pragma once

#include <AudioToolbox/AudioServices.h>
#include <AudioToolbox/AudioToolbox.h>
#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFURL.h>
#include <cstddef>
#include <string>

void playSound(const std::string &path);
