#include "include/native_collator/native_collator_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "native_collator_plugin.h"

void NativeCollatorPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  native_collator::NativeCollatorPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
