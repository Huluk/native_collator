import 'dart:async';
import 'package:flutter/services.dart';

/// Example:
///
/// ```dart
/// import 'package:native_collator/native_collator.dart';
///
/// void main() async {
///   final items = ['świnia', 'szafa', 'sok', 'tata'];
///   final sorted = await NativeCollator.sort(items, 'pl');
///   print(sorted);
/// }
/// ```
class NativeCollator {
  static const MethodChannel _channel = MethodChannel('native_collator');

  static Future<List<String>> sort(List<String> input, String locale) async {
    final sorted = await _channel.invokeMethod<List<dynamic>>('sortStrings', {
      'input': input,
      'locale': locale,
    });
    return sorted!.cast<String>();
  }

  static Future<List<T>> sortBy<T>(
    List<T> items,
    String Function(T) keyOf, {
    required String locale,
  }) async {
    final indices = await _channel.invokeMethod<List<dynamic>>('sortIndices', {
      'input': items.map(keyOf).toList(),
      'locale': locale,
    });
    return indices!.map((i) => items[i as int]).toList();
  }
}
