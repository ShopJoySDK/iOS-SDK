//
//  ShopJoyHeaders.h
//  ShopJoySDK
//
//  Copyright (c) 2014 ShopJoy. All rights reserved.
//

// ShopJoy campaign object
@interface ShopJoyCampaign : NSObject <NSCoding>
@property NSArray *beaconIDs;
@property NSInteger revision;
@property NSString *campaignID;
@property NSString *baseCampaignID;
@property Boolean active;
@property Boolean read;
@property NSInteger triggerRange;
@property NSDate *lastDownload;
@property NSDate *lastTrigger;
@property NSDate *endDate;
@property NSString *title;
@property NSString *notificationText;
@property NSString *summary;
@property NSInteger triggerDelay;
@property NSString *contentType;
@property NSString *contentData;
@property NSArray *timeslots;
@end

@interface ShopJoyQuest : NSObject <NSCoding>
@property NSString *questID;
@property Boolean active;
@property Boolean read;
@property NSDate *lastDownload;
@property NSDate *lastTrigger;
@property NSDate *endDate;
@property NSString *title;
@property NSString *notificationText;
@property NSString *summary;
@property NSArray *campaignIDs;
@property NSString *contentType;
@property NSString *contentData;
@end

// ShopJoyManager's delegate
@protocol ShopJoyManagerDelegate
- (void)shopJoyCampaignTriggered:(ShopJoyCampaign *)campaign;
- (void)shopJoyManagerEncounteredErrorWithCode:(NSInteger)code description:(NSString *)description;
- (void)shopJoyReportsOutdatedCampaign:(ShopJoyCampaign *)campaign;
@optional
- (void)shopJoyQuestCompleted:(ShopJoyQuest *)quest;
- (void)shopJoyQuestPartlyCompleted:(ShopJoyQuest *)quest;
- (void)shopJoyReportsBluetoothState:(Boolean)ready;
- (void)shopJoyReportsBackgroundMode:(Boolean)enabled;
@end

// ShopJoyManager
@interface ShopJoyManager : NSObject
- (id)initWithAPIKey:(NSString *)key logging:(BOOL)logging enableBluetoothSystemPrompt:(BOOL)bluetoothSystemPrompt userIdentifier:(NSString *)identifier delegate:(id)delegate;
- (void)startMonitoring;
- (void)stopMonitoring;
- (void)emptyCampaignMemory;
// campaign methods
- (void)removeCampaignFromMemory:(ShopJoyCampaign *)campaign;
- (void)openedCampaign:(ShopJoyCampaign *)campaign fromNotification:(BOOL)fromNotification;
- (NSArray *)returnCampaignMemory;
- (ShopJoyCampaign *)campaignWithId:(NSString *)campaignID;
// quest methods
- (void)removeQuestFromMemory:(ShopJoyQuest *)quest;
- (void)openedQuest:(ShopJoyQuest *)quest fromNotification:(BOOL)fromNotification;
- (NSArray *)returnQuestMemory;
- (ShopJoyQuest *)questWithId:(NSString *)questID;
// ShopJoy Manager delegate
@property (weak, nonatomic) id<ShopJoyManagerDelegate> delegate;
@end

// ShopJoy error codes
enum {
    SJBackgroundRefreshFailure = 1,
    SJBluetoothFailure = 2,
    SJLocationManagerFailure = 3,
    SJCampaignDownloadFailure = 4,
    SJAnalyticsError = 5,
    SJGenericFailure
};