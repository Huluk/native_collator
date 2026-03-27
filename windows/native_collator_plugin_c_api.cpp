#include "include/native_collator/native_collator_plugin_c_api.h"
#include "include/native_collator/native_collator_plugin.h"

#include <flutter/plugin_registrar_windows.h>

#include "native_collator_plugin.h"

static void RegisterPlugin(FlutterDesktopPluginRegistrarRef registrar) {
  native_collator::NativeCollatorPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}

void NativeCollatorPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  RegisterPlugin(registrar);
}

void NativeCollatorPluginRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  RegisterPlugin(registrar);
}
