//
//  ODInstallSDK.h
//  ODInstallSDK
//
//  Created by nathan on 2019/12/25.
//  Copyright © 2019 odin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ODInstallData.h"


@protocol ODInstallDelegate <NSObject>

@optional

/**
 * 唤醒时获取h5页面动态参数（如果是渠道链接，渠道编号会一起返回）
 * @param appData 动态参数对象
 */
- (void)getWakeUpParams:(nullable ODInstallData *)appData;

@end

@interface ODInstallSDK : NSObject

+ (NSString *_Nullable)sdkVersion;

+ (instancetype _Nullable)defaultManager;

/**
 * 初始化Install SDK
 * @param delegate 委托方法所在的类的对象
 */
+ (void)initWithDelegate:(id<ODInstallDelegate> _Nonnull)delegate;

///----------------------
/// @name 获取安装的动态参数
///----------------------
/**
 * @param completedBlock 回调block，在主线程（UI线程）回调
 *
 */
- (void)getInstallParmsCompleted:(void (^_Nullable)(ODInstallData*_Nullable appData))completedBlock;


/**
 * 开发者在需要获取用户安装app后由web网页传递过来的”动态参数“（如邀请码、游戏房间号，渠道编号等）时调用该方法,可第一时间返回数据，可在任意位置调用
 *
 * @param timeoutInterval 可设置回调超时时长，单位秒(s)
 * @param completedBlock 回调block，在主线程（UI线程）回调
 */
- (void)getInstallParmsWithTimeoutInterval:(NSTimeInterval)timeoutInterval
                                completed:(void (^_Nullable)(ODInstallData*_Nullable appData))completedBlock;

///---------------------
/// @name 一键拉起回调处理
///---------------------

/**
 * 处理 URI schemes
 * @param URL 系统回调传回的URL
 * @return bool URL是否被ODInstall识别
 */
+ (BOOL)handLinkURL:(NSURL *_Nullable)URL;


/**
 * 处理 通用链接
 * @param userActivity 存储了页面信息，包括url
 * @return bool URL是否被ODInstall识别
 */
+ (BOOL)continueUserActivity:(NSUserActivity *_Nullable)userActivity;



#pragma mark --统计相关

/**
 * 注册量统计
 *
 * 使用install 控制中心提供的渠道统计时，在App用户注册完成后调用，可以统计渠道注册量。
 * 必须在注册成功的时再调用该方法，避免重复调用，否则可能导致注册统计不准
 */


/// 注册量统计
/// @param userId 用户Id
/// @param phone 用户电话
/// @param email 用户邮箱
/// @param completeBlock 完成回调
- (void)reportRegister:(NSString *_Nullable)userId phone:(NSString * _Nullable)phone email:(NSString *_Nullable)email completeBlock:(void(^_Nullable)(NSString * _Nullable upUserId,NSError * _Nullable error))completeBlock;


/// 获取分享链接
/// @param shareParams 分享自定义参数
/// @param userId 当前用户id给下一级用户
/// @param shareUrlBlock 获取完成
- (void)getShareUrlPath:(NSDictionary *_Nullable)shareParams userId:(NSString *_Nonnull)userId shareUrlBlock:(void(^_Nullable)(NSString * _Nullable shareUrl,NSError * _Nullable error))shareUrlBlock;

- (void)logOn:(BOOL)logOn;
@end
