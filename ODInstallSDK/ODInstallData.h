//
//  ODinstallData.h
//  ODInstallSDK
//
//  Created by nathan on 2019/12/25.
//  Copyright © 2019 odin. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ODInstallData : NSObject

@property (nonatomic,strong) NSDictionary *data;//动态参数

@property (nonatomic,copy) NSString *channelCode;//渠道编号

- (instancetype)initWithData:(NSDictionary *)data
                 channelCode:(NSString *)channelCode;

@end

NS_ASSUME_NONNULL_END
