# Build Setup for iOS

## 1. Add the following libraries to your "Link Binary with Libraries" in Targets > Build Phases :

- [x] `WebKit.framework`
- [x] `SystemConfiguration.framework`
- [x] `CoreTelephony.framework`
- [x] `libsqlite3.0`
- [x] `libc++`
- [x] `libz`

Add "URL Schema" as your app id for "URL type" in Targets > info, See 
the following screenshot for the view on your XCode:

![Set URL Schema in XCode](./../image/url-types.png)

Cannot go back to APP from WeChat without configuration.  
如果不配置，就无法从微信重新回到APP。    
</br>
</br>
On iOS 9+, add `wechat` and `weixin` into `LSApplicationQueriesSchemes` in 
`Targets` > `info` > `Custom iOS Target Properties`. Or edit `Info.plist` 
then add:

```xml
<key>LSApplicationQueriesSchemes</key>
<array>
  <string>weixin</string>
  <string>wechat</string>
  <string>weixinULAPI</string>
</array>
```
If not configured, apple will prevent you from jumping to WeChat due to security permissions.  
如果不配置，因为安全权限问题，苹果会阻止你跳转到微信。  
</br>

## 2. Then copy the following in `AppDelegate.m`:  

wechat callback function, If not configured, When sharing is called, it appears "connecting" and then bounces back.  
微信回调方法，如果不配置，分享的时候微信会出现"正在连接"，然后直接弹回APP。

```objc
#import "WechatLib.h"

- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url {
    // 必须把回调交给 WechatLib，才能向 JS 发送 WeChat_Resp（含小程序唤起结果）
    return [WechatLib handleOpenURL:url];
}

- (BOOL)application:(UIApplication *)application
  continueUserActivity:(NSUserActivity *)userActivity
  restorationHandler:(void(^)(NSArray<id<UIUserActivityRestoring>> * __nullable
  restorableObjects))restorationHandler {
  [RCTLinkingManager application:application continueUserActivity:userActivity restorationHandler:restorationHandler];
  return [WechatLib handleOpenUniversalLink:userActivity];
}
```
Universal Links config, If not used, please ignore.  
Universal Links 配置文件, 没使用的话可以忽略。
```objc
#import <React/RCTLinkingManager.h>
#import "WechatLib.h"

// ios 9.0+
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url
            options:(NSDictionary<NSString*, id> *)options
{
  [RCTLinkingManager application:application openURL:url options:options];
  return [WechatLib handleOpenURL:url];
}
```
**注意：**
1. 不要使用 `delegate:self`（AppDelegate 未实现 `onResp` 时 JS 收不到回调）。
2. 不使用 Universal Links 会导致微信支付 / 小程序回跳后无法获取回调事件。
## 3. Then copy the following in `AppDelegate.h`: 
```
#import <React/RCTBridgeDelegate.h>
#import <UIKit/UIKit.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate, RCTBridgeDelegate>

@property (nonatomic, strong) UIWindow *window;

@end
```
AppDelegate 无需再实现 `WXApiDelegate`；回调由 `WechatLib` 模块处理。

## 4. 从版本 3.0.0 开始，需要手动导入 libWeChatSDK.a 到 XCode
直接复制本项目的 /ios/libWeChatSDK.a 到 Xcode 项目根目录，详细可参考 example 工程
