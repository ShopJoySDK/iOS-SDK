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
/*!
 @abstract ShopJoySDKDelegate. Belongs to the ShopJoyManager object.
 */
@protocol ShopJoyManagerDelegate
/*!
 @abstract Will be called when the ShopJoyManager encountered an error.
 @return void
 @param code A ShopJoyErrorCodes: 1. SJBackgroundRefreshFailure, 2. SJBluetoothFailure, 3. SJLocationManagerFailure, 4. SJCampaignDownloadFailure, 5. SJAnalyticsError.
 @param description A description of the encountered error.
 */
- (void)shopJoyManagerEncounteredErrorWithCode:(NSInteger)code description:(NSString *)description;
/*!
 @abstract Will be called when a campaign is triggered.
 @return void
 @param campaign The ShopJoyCampaign object corresponding to the campaign that has been triggered
 */
- (void)shopJoyCampaignTriggered:(ShopJoyCampaign *)campaign;
/*!
 @abstract Will be called when an outdated campaign is opened by the user.
 @return void
 @param campaign The outdated ShopJoyCampaign
 */
- (void)shopJoyReportsOutdatedCampaign:(ShopJoyCampaign *)campaign;
@optional
/*!
 @abstract This method will be called when a quest is completed.
 @param quest The completed quest
 @return void
 */
- (void)shopJoyQuestCompleted:(ShopJoyQuest *)quest;
/*!
 @abstract This method will be called when a quest is partly, completed, so when a campaign beloning to a quest is fired.
 @param quest The completed quest
 @return void
 */
- (void)shopJoyQuestPartlyCompleted:(ShopJoyQuest *)quest;
/*!
 @abstract Will be called when the device's Bluetooth state has changed. This method can be used to present or hide a warning message.
 @return void
 @param ready A boolean representing the device's Bluetooth state.
 */
- (void)shopJoyReportsBluetoothState:(Boolean)ready;
/*!
 @abstract Will report the device's background mode. This method can be used to present or hide a warning message.
 @return void
 @param enabled A boolean representing the device's background mode state.
 */
- (void)shopJoyReportsBackgroundMode:(Boolean)enabled;

@end

@protocol ShopJoyQuestManagerDelegate;
@protocol ShopJoyLocationManagerDelegate;

/*!
 @abstract Initialize ShopJoyManager and set/implement it's delegate to start receiving ShopJoy campaign notifications.
 @return void
 */
@interface ShopJoyManager : NSObject
/*!
 DEPRECATED: Use initWithAPIKey:logging:userIdentifier:delegate:
 @abstract Initialize a ShopJoyManager object. Provide a valid API key, enable/disable logging (XCode console logs about what is going on "under the hood" of the ShopJoyManager) and, optionally, set a user identifier. This is a unique key to identify individual users in ShopJoy's analytics. If not provided, a random UUID will be used and stored on the user's device. This UUID will be lost on device change.
 @return id
 @param key A ShopJoy API key.
 @param bluetoothSystemPrompt Should the prompt show up or not
 @param logging A boolean to enable (YES) or disable (NO) logging events in XCode's console. Default is NO.
 @param identifier Any string that is unique for the user. If not provided, the SDK will create, store and use a random UUID. When a ShopJoy user logs in later on, this ID is overwritten.
 @param delegate Set the delegate for ShopJoy methods here.
 */
- (id)initWithAPIKey:(NSString *)key logging:(BOOL)logging enableBluetoothSystemPrompt:(BOOL)bluetoothSystemPrompt userIdentifier:(NSString *)identifier delegate:(id)delegate __deprecated_msg("Use initWithAPIKey:logging:userIdentifier:delegate:");
/*!
 @abstract Initialize a ShopJoyManager object. Provide a valid API key, enable/disable logging (XCode console logs about what is going on "under the hood" of the ShopJoyManager) and, optionally, set a user identifier. This is a unique key to identify individual users in ShopJoy's analytics. If not provided, a random UUID will be used and stored on the user's device. This UUID will be lost on device change.
 @return id
 @param key A ShopJoy API key.
 @param logging A boolean to enable (YES) or disable (NO) logging events in XCode's console. Default is NO.
 @param identifier Any string that is unique for the user. If not provided, the SDK will create, store and use a random UUID. When a ShopJoy user logs in later on, this ID is overwritten.
 @param delegate Set the delegate for ShopJoy methods here.
 */
- (id)initWithAPIKey:(NSString *)key logging:(BOOL)logging userIdentifier:(NSString *)identifier delegate:(id)delegate;
/*!
 @abstract Use this method to change the userID.
 @param logging Boolean setting whether logs about ShopJoy's activity should be logged to the console or not
 @param bluetoothPrompt Boolean setting whether user should be reminded to turn on Bluetooth when it's turned off.
 @param identifier Any string that is unique for the user. If not provided, the SDK will create, store and use a random UUID untill a ShopJoy user is logged in. When a ShopJoy user logs in later on, this ID is overwritten.
 @return void.
 */
- (void)setUserID:(NSString *)identifier;
/*!
 @abstract Starts the monitoring for ShopJoy campaigns. If necessary, this method will invoke a Location Services permission request
 @return void
 */
- (void)startMonitoring;
/*!
 @abstract Stops the monitoring for ShopJoy campaigns.
 @return void
 */
- (void)stopMonitoring;
/*!
 @abstract Call to empty ShopJoyManager's memory. This will erase all campaigns and quests. After calling this method all found beacons/campaigns will be considered "new".
 @return void
 */
- (void)emptyCampaignMemory;
/*!
 @abstract Call to remove a specific campaign from ShopJoyManager's memory.
 @param campaign The ShopJoyCampaign object that should be removed from memory
 @return void
 */
- (void)removeCampaignFromMemory:(ShopJoyCampaign *)campaign;
/*!
 @abstract Call to mark a specific campaign in ShopJoyManager's memory as read, and at the same time check it's validity. If a campaign is invalid, the shopJoyReportsOutdatedCampaign: method will be called. This method will log an analytics event to the CMS.
 @param campaign The ShopJoyCampaign object that should be marked as read
 @param fromNotification Pass BOOL here. Used for analytics: deciding whether user opened campaign from app or from notification
 @return void
 */
- (void)openedCampaign:(ShopJoyCampaign *)campaign fromNotification:(BOOL)fromNotification;
/*!
 @abstract Returns an array with all ShopJoyCampaign objects that have been encountered. The emptyCampaignMemory method will empty this memory. Always check the "active" properties before presenting it to a user.
 @return NSArray.
 */
- (NSArray *)returnCampaignMemory;
/*!
 @abstract This method returns a ShopJoyCampaign object corresponding to the supplied BaseCampaignID. Returns nil if no corresponding campaign is found.
 @param campaignID The BaseCampaignID
 @return ShopJoyCampaign.
 */
- (ShopJoyCampaign *)campaignWithId:(NSString *)campaignID;

// QUESTS
/*!
 @abstract Call to remove a specific quest from ShopJoyManager's memory.
 @param quest The ShopJoyQuest object that should be removed from memory
 @return void
 */
- (void)removeQuestFromMemory:(ShopJoyQuest *)quest;
/*!
 @abstract Call to mark a specific quest in ShopJoyManager's memory as read. This method will log an analytics event to the CMS.
 @param quest The ShopJoyQuest object that should be marked as read
 @param fromNotification Pass BOOL here. Used for analytics: deciding whether user opened campaign from app or from notification
 @return void
 */
- (void)openedQuest:(ShopJoyQuest *)quest fromNotification:(BOOL)fromNotification;
/*!
 @abstract Returns an array with all ShopJoyQuest objects that have been encountered. The emptyCampaignMemory method will empty this memory. Always check the "active" properties before presenting it to a user.
 @return NSArray.
 */
- (NSArray *)returnQuestMemory;
/*!
 @abstract This method returns a ShopJoyQuest object corresponding to the supplied quest ID. Returns nil if no corresponding quest is found.
 @param questID The quest ID
 @return ShopJoyQuest.
 */
- (ShopJoyQuest *)questWithId:(NSString *)questID;

+ (NSString *)apiURL;
+ (NSString *)apiKey;
+ (NSString *)userIdentifier;
+ (Boolean)loggingEnabled;

/*!
 @abstract ShopJoyManagerDelegate
 */

@property (weak, nonatomic) id<ShopJoyManagerDelegate> delegate;
@end