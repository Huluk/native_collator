import Cocoa
import FlutterMacOS

public class NativeCollatorPlugin: NSObject, FlutterPlugin {
  public static func register(with registrar: FlutterPluginRegistrar) {
    let channel = FlutterMethodChannel(name: "native_collator", binaryMessenger: registrar.messenger)
    let instance = NativeCollatorPlugin()
    registrar.addMethodCallDelegate(instance, channel: channel)
  }

  public func handle(_ call: FlutterMethodCall, result: @escaping FlutterResult) {
    if call.method == "sortStrings",
      let args = call.arguments as? [String: Any],
      let input = args["input"] as? [String],
      let locale = args["locale"] as? String
    {
      let localeObj = Locale(identifier: locale)
      let sorted = input.sorted { $0.compare($1, locale: localeObj) == .orderedAscending }
      result(sorted)
    } else if call.method == "sortIndices",
      let args = call.arguments as? [String: Any],
      let input = args["input"] as? [String],
      let locale = args["locale"] as? String
    {
      let localeObj = Locale(identifier: locale)
      let indices = input.indices.sorted { input[$0].compare(input[$1], locale: localeObj) == .orderedAscending }
      result(indices)
    } else {
      result(FlutterMethodNotImplemented)
    }
  }
}
