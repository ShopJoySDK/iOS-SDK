ShopJoy iOS SDK


Changelog
=============

1.5.4
====
- Fat library with i386 architecture

1.5.3
====
- Mini bug fix

1.5.2
====
- Performance improvements

1.5.1
====
- Fixed a bug related to having one campaign connected to multiple beacons
- Made the iOS Bluetooth system prompt optional
- shopJoyReportsBackGroundMode: and shopJoyReportsBluetoothState: delegate methods are now optional
- Changed “notificationText” property to ShopJoyCampaign object. This property will string-replace “%” by “%%” to make it suitable for displaying in a push message
- The same string as notificationText, but with just 1 “%”, will be provided through the “summary” property of ShopJoyCampaign objects.

1.5
====
- Added quest functionality
- SDK now checks for Bluetooth without prompting
- ShopJoyManagerDelegate is a weak property now
- shopJoyReportsOutdatedCampaign:(NSString *)campaignID is now shopJoyReportsOutdatedCampaign:(ShopJoyCampaign *)campaign;
- Removed objects, methods, errors and enums related to ShopJoyUser
- Fix for displaying %-signs in notification text

1.4.3
====
- Added support for complex URL's
- Fixed a bug that could occur when having multiple campaigns on one beacon

1.4.2
=====
- Removed background mode requirement
- Integrated setting of delegate in initWithApiKey:method

1.4.1
=====
- Fixed a bug that caused a lot of CMS requests in specific cases