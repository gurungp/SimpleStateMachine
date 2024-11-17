
#pragma once
#include "PlaySound.h"
#include <iostream>

void playSound(const std::string &path) {

  CFStringRef cfPath = CFStringCreateWithCString(NULL, path.c_str(), kCFStringEncodingUTF8);
  CFURLRef soundURL = CFURLCreateWithFileSystemPath(NULL, cfPath, kCFURLPOSIXPathStyle, false);
  SystemSoundID soundID;

  if (AudioServicesCreateSystemSoundID(soundURL, &soundID) == kAudioServicesNoError) {
    AudioServicesPlaySystemSound(soundID);
  } else {
    std::cout << "Unable to play Sound" << std::endl;
  }

  CFRelease(soundURL);
  CFRelease(cfPath);
}
