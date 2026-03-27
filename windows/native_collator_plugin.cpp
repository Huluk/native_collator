#include "native_collator_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <algorithm>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

namespace native_collator {

static std::wstring Utf8ToWide(const std::string& utf8) {
  if (utf8.empty()) return {};
  int size = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);
  // TODO GetLastError to find out exact error case, see
  // https://learn.microsoft.com/en-us/windows/win32/api/stringapiset/nf-stringapiset-multibytetowidechar#return-value
  if (size <= 0) return {};
  std::wstring wide(size - 1, L'\0');
  MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, wide.data(), size);
  return wide;
}

// static
void NativeCollatorPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "native_collator",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<NativeCollatorPlugin>();

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

NativeCollatorPlugin::NativeCollatorPlugin() {}

NativeCollatorPlugin::~NativeCollatorPlugin() {}

void NativeCollatorPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  if (method_call.method_name() == "sortStrings") {
    const auto* args =
        std::get_if<flutter::EncodableMap>(method_call.arguments());
    if (!args) {
      result->Error("BAD_ARGS", "Expected a map of arguments");
      return;
    }

    auto input_it = args->find(flutter::EncodableValue("input"));
    auto locale_it = args->find(flutter::EncodableValue("locale"));
    if (input_it == args->end() || locale_it == args->end()) {
      result->Error("BAD_ARGS", "Missing 'input' or 'locale'");
      return;
    }

    const auto* input_list =
        std::get_if<flutter::EncodableList>(&input_it->second);
    const auto* locale_utf8 =
        std::get_if<std::string>(&locale_it->second);
    if (!input_list || !locale_utf8) {
      result->Error("BAD_ARGS", "Invalid argument types");
      return;
    }

    // CompareStringEx expects a BCP 47 locale name (hyphens, not underscores).
    std::wstring locale = Utf8ToWide(*locale_utf8);
    for (auto& c : locale) {
      if (c == L'_') c = L'-';
    }

    std::vector<std::wstring> wide_strings;
    wide_strings.reserve(input_list->size());
    for (const auto& item : *input_list) {
      const auto* s = std::get_if<std::string>(&item);
      wide_strings.push_back(s ? Utf8ToWide(*s) : std::wstring{});
    }

    std::vector<size_t> indices(wide_strings.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::stable_sort(indices.begin(), indices.end(),
        [&](size_t a, size_t b) {
          int cmp = CompareStringEx(
              locale.c_str(), NORM_LINGUISTIC_CASING,
              wide_strings[a].c_str(), -1,
              wide_strings[b].c_str(), -1,
              nullptr, nullptr, 0);
          // Fallback to string sort in case of CompareStringEx error.
          if (cmp == 0) return wide_strings[a] < wide_strings[b];
          return cmp == CSTR_LESS_THAN;
        });

    flutter::EncodableList sorted;
    sorted.reserve(indices.size());
    for (size_t i : indices) {
      const auto* s = std::get_if<std::string>(&(*input_list)[i]);
      sorted.push_back(flutter::EncodableValue(s ? *s : std::string{}));
    }

    result->Success(flutter::EncodableValue(sorted));
  } else {
    result->NotImplemented();
  }
}

}  // namespace native_collator
