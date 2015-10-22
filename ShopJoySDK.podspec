Pod::Spec.new do |s|
	s.name = "ShopJoySDK"
	s.version = "1.5.6"
	s.summary = "ShopJoySDK"
	s.description = "SDK for ShopJoy"
	s.license = '(c) ShopJoy 2015. All rights reserved.'
  	s.authors = { 'Mathijs Vreeman' => 'mathijs.vreeman@shopjoy.se' }
	s.homepage = "https://github.com/ShopJoySDK/iOS-SDK/"
	s.platform = :ios, "7.0"
	s.source_files = "*.h"
	s.source = { :git => 'https://github.com/ShopJoySDK/iOS-SDK.git', :tag => s.version }
	s.requires_arc = true
	s.xcconfig = { 	"FRAMEWORK_SEARCH_PATHS" => "$(inherited)",
					"HEADER_SEARCH_PATHS" => "$(inherited)"}
	s.preserve_paths = "libShopJoySDK.a"
	s.vendored_libraries = "libShopJoySDK.a"
	s.frameworks = 'CoreBluetooth', 'CoreLocation'
end