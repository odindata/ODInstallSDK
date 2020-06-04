# ODInstallSDK
![Build Status](https://img.shields.io/badge/pod-0.0.3-blue.svg)
![Build Status](https://img.shields.io/badge/platform-iOS-dark.svg)

### ODInstallSDK高效App推广统计技术,无须渠道分包、免填推广码,即可实现海量渠道App安装业绩归属统计。优化用户体验,提升App推广转化率。  

---

#### ODInstallSDK使用步骤
 1. [安装](#install)
 2. [申请AppKey](#appkey)
 3. [配置AppKey](#appkeyconfig)
 4. [具体功能使用](#wayofuse)
 	- 4.1 [初始化](#init)
  	- 4.2 [获取唤醒参数](#wakeup)
  	- 4.3 [携带参数安装](#installParma)
  	- 4.4 [注册](#register)
  	- 4.5 [获取分享链接](#shareLink)
  
  	
  	
  	
  	
---

<h1 id="install">1.安装</h1>  

ODInstallSDK提供2种方式集成到工程中。
### 1.1 手动集成
在[奥丁数据开发者服务中心](http://www.odinanalysis.com/)下载ODInstallSDK的最新版本，并添加到项目中。  

通过**Build Settings** > **Other Linker Flags**，添加
> -ObjC  

如下图所示：  
![image](https://github.com/BaconTimes/files/blob/master/images/odinpushbuildsetting.png?raw=true)

### 1.2 pod集成
#### 1.2.1 启动命令行工具，切换到工程目录下，如果项目之前没有使用pod集成，那么执行

```shell
$ pod init
```
该命令会在当前目录下生产对应的Podfile文件。

#### 1.2.2 在Podfile中添加
> pod 'ODInstall'

#### 1.2.3 执行pod的集成命令

```shell
$ pod install
```

#### 1.2.4 如果安装失败，提示原因是没有找到ODInstall，那么执行以下命令更新本地库，然后再执行pod install

```shell
$ pod repo update
```
<h1 id="appkey">2.申请AppKey</h1>  

在[奥丁数据开发者服务中心](http://www.odinanalysis.com/)申请并获得ODInstall的**AppKey**。

![image](https://github.com/odindata/ODInstallSDK/blob/master/Files/key.png?raw=true)




<h1 id="appkeyconfig">3.配置AppKey</h1>  

在工程的**info.plist**进行配置，AppKey对应plist的key是**OdinKey**，string类型，AppSecret对应plist的key是**OdinSecret**，string类型。


```
<key>OdinKey</key>  
<string>填写你自己申请的AppKey</string>
<key>OdinSecret</key>  
<string>填写你自己申请的AppSecret </string>
```

<p align="center">
  <img src="https://github.com/BaconTimes/files/blob/master/images/odinpushprojinfo.png?raw=true" alt="OdinPush_info.plist" title="info.plist">
</p>

#### 网络请求权限配置  

由于OdinSMS的请求是http，需要运行app设置请求权限。源代码如下：

```
<key>NSAppTransportSecurity</key>  
<dict>  
<key>NSAllowsArbitraryLoads</key>  
<true/>  
</dict>  
```
开发者可以将上面代码直接加入到**info.plist**中。
或者自行添加，在info.plist最外层点击加号，添加新的键值对，key为**App Transport Security Settings**，类型为**Dictionary**，在刚添加的Dictionary下面添加键值对，key为**Allow Arbitrary Loads**，类型为**Boolean**，值为**YES**，如下图所示：  

![image](https://github.com/BaconTimes/files/blob/master/images/odinpushnetauth.png?raw=true)


<h1 id="wayofuse">4.具体功能使用</h1>  
<h2 id="init">4.1 初始化</h2>  

在AppDelegate中，增加头文件的引用：


```
#import "ODInstallSDK.h"
```

在
```application: didFinishLaunchingWithOptions:```方法中调用initWithDelegate方法来初始化SDK，如下代码所示：

```
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    [ODInstallSDK initWithDelegate:self];
    return YES;
}
```

<h2 id="wakeup">4.2 获取唤醒参数</h2>  

在XCode中配置当前应关联域名(Associated Domains)(只适用于iOS9以上)，
域名在奥丁开发者中心查看如下图：
![image](https://github.com/odindata/ODInstallSDK/blob/master/Files/config.png?raw=true)

 在xcode中配置上图的Associated Domains值
![image](https://github.com/odindata/ODInstallSDK/blob/master/Files/link.png?raw=true)

在AppDelegate中添加通用链接(Universal Link)回调方法，委托给ODinstallSDK来处理

```
- (BOOL)application:(UIApplication *)application continueUserActivity:(NSUserActivity *)userActivity restorationHandler:(void (^)(NSArray * _Nullable))restorationHandler{
    //判断是否通过ODInstall Universal Link 唤起App
    if ([ODInstallSDK continueUserActivity:userActivity]){//如果使用了Universal link ，此方法必写
        return YES;
    }
    //其他第三方回调；
     return YES;
}
```

集成Scheme(只适用于iOS9以下):

在Xcode里选中Target－Info－URL Types，给当前应用配置Scheme，Scheme值在开发者中心，如下图所示：
![image](https://github.com/odindata/ODInstallSDK/blob/master/Files/config.png?raw=true)
将ODInstall为当前应用生成的Scheme配置如下:
![image](https://github.com/odindata/ODInstallSDK/blob/master/Files/scheme.jpg?raw=trues)

在AppDelegate中添加Scheme回调方法，委托给ODInstallSDK来处理


```
//适用目前所有iOS版本
-(BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation{
    //判断是否通过OpenInstall URL Scheme 唤起App
    if  ([ODInstallSDK handLinkURL:url]){//必写
        return YES;
    }
    //其他第三方回调；
    return YES;

}

//iOS9以上，会优先走这个方法
- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(nonnull NSDictionary *)options{
    //判断是否通过OpenInstall URL Scheme 唤起App
    if  ([ODInstallSDK handLinkURL:url]){//必写
        return YES;
    }
    //其他第三方回调；
     return YES;

}
```

在AppDeletegate中遵守协议，添加一键拉起的回调，获取来自H5页面的动态参数，根据参数值直达具体页

```
//通过ODInstall获取已经安装App被唤醒时的参数（如果是通过渠道页面唤醒App时，会返回渠道编号）
-(void)getWakeUpParams:(ODInstallData *)appData{
    if (appData.data) {//(动态唤醒参数)
        //e.g.如免填邀请码建立邀请关系、自动加好友、自动进入某个群组或房间等
    }
    if (appData.channelCode) {//(通过渠道链接或二维码唤醒会返回渠道编号)
        //e.g.可自己统计渠道相关数据等
    }
    NSLog(@"ODInstallSDK:\n动态参数：%@;\n渠道编号：%@",appData.data,appData.channelCode);
}
```

<h2 id="installParma">4.3 携带参数安装</h2> 

在APP需要安装参数时（由web网页中传递过来的，如邀请码、游戏房间号等动态参数），调用getInstallParmsCompleted方法，在回调中获取参数（可重复获取）

```
[[ODInstallSDK defaultManager] getInstallParmsCompleted:^(ODInstallData*_Nullable appData) {
    //在主线程中回调
    if (appData.data) {//(动态安装参数)
       //e.g.如免填邀请码建立邀请关系、自动加好友、自动进入某个群组或房间等
    }
    if (appData.channelCode) {//(通过渠道链接或二维码安装会返回渠道编号)
        //e.g.可自己统计渠道相关数据等
    }
    NSLog(@"ODInstallSDK:\n动态参数：%@;\n渠道编号：%@",appData.data,appData.channelCode);
}];
```

<h2 id="register">4.4 用户注册</h2> 

```
[[ODInstallSDK defaultManager] reportRegister:@"userId" phone:@"phone" email:@"eamil" completeBlock:^(NSString * _Nullable upUserId, NSError * _Nullable error) {
    NSLog(@"upUserId:%@",upUserId);
}];
```

<h2 id="shareLink">4.5 获取分享链接</h2> 

```
[[ODInstallSDK defaultManager] getShareUrlPath:nil userId:userId shareUrlBlock:^(NSString * _Nullable shareUrl, NSError * _Nullable error) {
    NSLog(@"shareUrl:%@",shareUrl);
}];
```

