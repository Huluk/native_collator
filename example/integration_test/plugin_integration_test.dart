import 'package:flutter_test/flutter_test.dart';
import 'package:native_collator/native_collator.dart';
import 'package:integration_test/integration_test.dart';

void main() {
  IntegrationTestWidgetsFlutterBinding.ensureInitialized();

  test('sort orders Polish strings correctly', () async {
    final result = await NativeCollator.sort([
      'świnia',
      'szafa',
      'sok',
      'tata',
    ], 'pl');
    expect(result, equals(['sok', 'szafa', 'świnia', 'tata']));
  });

  test('sortBy orders German objects by name correctly', () async {
    final oel = {'name': 'Öl'};
    final apfel = {'name': 'Apfel'};
    final aepfel = {'name': 'Äpfel'};
    final zucker = {'name': 'Zucker'};
    final ueber = {'name': 'Über'};

    final result = await NativeCollator.sortBy(
      [oel, apfel, aepfel, zucker, ueber],
      (item) => item['name']!,
      locale: 'de',
    );
    expect(result, equals([apfel, aepfel, oel, ueber, zucker]));
  });

  test('sortBy is stable for equal keys', () async {
    final aepfel1 = {'name': 'Äpfel', 'id': 1};
    final aepfel2 = {'name': 'Äpfel', 'id': 2};
    final zucker = {'name': 'Zucker', 'id': 3};
    final ueber = {'name': 'Über', 'id': 4};

    final result = await NativeCollator.sortBy(
      [zucker, aepfel1, ueber, aepfel2],
      (item) => item['name']! as String,
      locale: 'de',
    );
    expect(result, equals([aepfel1, aepfel2, ueber, zucker]));
  });

  test('sortBy preserves object identity', () async {
    final sok = {'name': 'sok', 'id': 1};
    final szafa = {'name': 'szafa', 'id': 2};
    final swinia = {'name': 'świnia', 'id': 3};

    final result = await NativeCollator.sortBy(
      [swinia, szafa, sok],
      (item) => item['name']! as String,
      locale: 'pl',
    );
    expect(result, equals([sok, szafa, swinia]));
    expect(result.map((r) => r['name']), equals(['sok', 'szafa', 'świnia']));
    expect(result.map((r) => r['id']), equals([1, 2, 3]));
  });
}
