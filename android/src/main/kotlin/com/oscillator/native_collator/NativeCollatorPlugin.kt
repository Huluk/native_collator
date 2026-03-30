package com.oscillator.native_collator

import androidx.annotation.NonNull
import io.flutter.embedding.engine.plugins.FlutterPlugin
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel
import java.text.Collator
import java.util.*

class NativeCollatorPlugin: FlutterPlugin, MethodChannel.MethodCallHandler {
  private lateinit var channel : MethodChannel

  override fun onAttachedToEngine(@NonNull flutterPluginBinding: FlutterPlugin.FlutterPluginBinding) {
    channel = MethodChannel(flutterPluginBinding.binaryMessenger, "native_collator")
    channel.setMethodCallHandler(this)
  }

  override fun onMethodCall(@NonNull call: MethodCall, @NonNull result: MethodChannel.Result) {
    if (call.method == "sortStrings") {
      val input = call.argument<List<String>>("input") ?: emptyList()
      val localeStr = call.argument<String>("locale") ?: "en"
      val collator = Collator.getInstance(Locale.forLanguageTag(localeStr))
      val sorted = input.sortedWith(collator)
      result.success(sorted)
    } else if (call.method == "sortIndices") {
      val input = call.argument<List<String>>("input") ?: emptyList()
      val localeStr = call.argument<String>("locale") ?: "en"
      val collator = Collator.getInstance(Locale.forLanguageTag(localeStr))
      val indices = input.indices.sortedWith { a, b -> collator.compare(input[a], input[b]) }
      result.success(indices)
    } else {
      result.notImplemented()
    }
  }

  override fun onDetachedFromEngine(@NonNull binding: FlutterPlugin.FlutterPluginBinding) {
    channel.setMethodCallHandler(null)
  }
}
