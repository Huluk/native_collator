#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html.
# Run `pod lib lint native_collator.podspec` to validate before publishing.
#
Pod::Spec.new do |s|
  s.name             = 'native_collator'
  s.version          = '0.0.1'
  s.summary          = 'Locale-aware string sorting via platform ICU.'
  s.description      = <<-DESC
Locale-aware string sorting via platform ICU using Flutter's platform channels.
                       DESC
  s.homepage         = 'https://github.com/MichalDanielDobrzanski/native_collator'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'Michał Dobrzański' => 'dobrzanskioscillator@gmail.com' }

  s.source           = { :path => '.' }
  s.source_files = 'Classes/**/*'

  # If your plugin requires a privacy manifest, for example if it collects user
  # data, update the PrivacyInfo.xcprivacy file to describe your plugin's
  # privacy impact, and then uncomment this line. For more information,
  # see https://developer.apple.com/documentation/bundleresources/privacy_manifest_files
  # s.resource_bundles = {'native_collator_privacy' => ['Resources/PrivacyInfo.xcprivacy']}

  s.dependency 'FlutterMacOS'

  s.platform = :osx, '10.11'
  s.pod_target_xcconfig = { 'DEFINES_MODULE' => 'YES' }
  s.swift_version = '5.0'
end
