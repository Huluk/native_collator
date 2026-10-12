// swift-tools-version: 5.9

import PackageDescription

let package = Package(
    name: "native_collator",
    platforms: [
        .iOS("12.0")
    ],
    products: [
        .library(name: "native-collator", targets: ["native_collator"])
    ],
    dependencies: [
        .package(name: "FlutterFramework", path: "../FlutterFramework")
    ],
    targets: [
        .target(
            name: "native_collator",
            dependencies: [
                .product(name: "FlutterFramework", package: "FlutterFramework")
            ],
            resources: [
                .process("PrivacyInfo.xcprivacy")
            ]
        )
    ]
)
