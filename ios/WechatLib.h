#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <React/RCTBridgeModule.h>
#import "WXApi.h"

// define share type constants
#define RCTWXShareTypeNews @"news"
#define RCTWXShareTypeThumbImageUrl @"thumbImage"
#define RCTWXShareTypeImageUrl @"imageUrl"
#define RCTWXShareTypeImageFile @"imageFile"
#define RCTWXShareTypeImageResource @"imageResource"
#define RCTWXShareTypeText @"text"
#define RCTWXShareTypeVideo @"video"
#define RCTWXShareTypeAudio @"audio"
#define RCTWXShareTypeFile @"file"

#define RCTWXShareType @"type"
#define RCTWXShareTitle @"title"
#define RCTWXShareDescription @"description"
#define RCTWXShareWebpageUrl @"webpageUrl"
#define RCTWXShareImageUrl @"imageUrl"

#define RCTWXEventName @"WeChat_Resp"
#define RCTWXEventNameWeChatReq @"WeChat_Req"

@interface WechatLib : NSObject <RCTBridgeModule, WXApiDelegate>

@property NSString* appId;

/**
 * 返回当前桥接模块实例，供 AppDelegate 将 WXApi 回调交给本模块处理。
 * 须在 RN bridge 创建 WechatLib 之后调用；过早调用会返回 nil。
 */
+ (instancetype)sharedInstance;

/**
 * 将 URL Scheme 回调交给微信 SDK，并由本模块转发 WeChat_Resp 到 JS。
 */
+ (BOOL)handleOpenURL:(NSURL *)url;

/**
 * 将 Universal Link 回调交给微信 SDK，并由本模块转发 WeChat_Resp 到 JS。
 */
+ (BOOL)handleOpenUniversalLink:(NSUserActivity *)userActivity;

@end
