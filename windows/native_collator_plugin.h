#ifndef FLUTTER_PLUGIN_NATIVE_COLLATOR_PLUGIN_H_
#define FLUTTER_PLUGIN_NATIVE_COLLATOR_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace native_collator {

class NativeCollatorPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  NativeCollatorPlugin();

  virtual ~NativeCollatorPlugin();

  // Disallow copy and assign.
  NativeCollatorPlugin(const NativeCollatorPlugin&) = delete;
  NativeCollatorPlugin& operator=(const NativeCollatorPlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

}  // namespace native_collator

#endif  // FLUTTER_PLUGIN_NATIVE_COLLATOR_PLUGIN_H_
