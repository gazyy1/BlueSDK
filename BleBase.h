//
//  BleBase.h
//  SDK专用测试
//
//  Created by zhai on 2017/11/14.
//  Copyright © 2017年 zhai. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

@protocol bleCallBackDelegate <NSObject>
@optional
//返回信息
- (void)bleCallBack:(NSDictionary *)dic;
@end

@interface BleBase : NSObject<bleCallBackDelegate,CBPeripheralDelegate,CBCentralManagerDelegate>

//SDK初始化
- (instancetype)initWithDelegate:(id<bleCallBackDelegate>)delegate;
/*  * 连接蓝牙BLE设备。  *  * @param peripheral当前控制器蓝牙周边设备；  * @param manager当前控制器蓝牙中心设备；  * @param devID 蓝牙BLE设备的ID，可以是空字符串；  * @param devSecret 蓝牙BLE设备的秘钥，不可以是空字符串；  * @param userID 连接蓝牙BLE设备的用户 可以是空字符串。  */
-(void)bleConnectWithPeripheral:(CBPeripheral*)peripheral
                        manager:(CBCentralManager*)manager
                          devID:(NSString*)devID
                      devSecret:(NSString*)devSecret
                         userID:(NSString *)userID;

/**  * 断开蓝牙BLE设备连接。
 */
-(void)bleDisConnect;
/**   * 获取蓝牙BLE钥匙基本信息。
 */
-(void)getBleDeviceInfo;
/**   * 获取锁芯识别号，即锁芯ID。   */
-(void)getLockCode;
/**  * 获取蓝牙BLE钥匙识别号，即钥匙ID。
 */
-(void)getKeyCode;
/**  * 获取锁状态。
 */
-(void)getLockState;
/**      * 初始化蓝牙BLE钥匙。      *      * @param newID 指定新的蓝牙BLE钥匙ID，即识别码；如果为空字符串或者与当前ID相同，那么不修改识别码。      * @param newSecret 指定新的秘钥；如果为空字符串，那么不修改秘钥。      *                  如果秘钥数据比较复杂，那么可以是一串JSON字符串，由底层程序来处理这串字符串。      * @param validityPeriod 指定蓝牙BLE钥匙脱机有效期(单位:小时)，即蓝牙BLE过多长时间必须通过APP重新连接一次，否则所有权限失效。      *                  如果蓝牙BLE钥匙上的授权长期有效，那么蓝牙BLE钥匙被别人捡到就有可能造成损失，为此，必须做个权限超时。
 */
-(void)initKey:(NSString*)newID
     newSecret:(NSString*)newSecret
validityPeriod:(int)validityPeriod;
/**      *  把蓝牙BLE钥匙和用户解绑。删除用户所以授权信息。      *  蓝牙BLE钥匙初始化时，初始化函数应该自动和用户绑定的，当用户不用蓝牙钥匙时，最好主动解绑，这样确保授权信息得到删除。
 */
-(void)unbindKey;
/**      * 初始化电子锁芯。      *      * @param lockCode 指定锁芯ID，即识别码，如果初始无ID，那么可以输入空字符串。      * @param newLockCode 指定新的锁芯ID，即识别码；如果为空字符串，那么不修改识别码。      * @param newSecret 指定新的锁芯秘钥；如果为空字符串，那么不修改秘钥。      *                  如果秘钥数据比较复杂，那么可以是一串JSON字符串，由底层程序来处理这串字符串。
 */
-(void)initDoorLock:(NSString*)lockCode
        newLockCode:(NSString*)newLockCode
          newSecret:(NSString*)newSecret;
/**      * 设置蓝牙BLE钥匙的时间。      *      * @param currentDate 指定当前时间。
 */
-(void)setBleTime:(NSDate*)currentDate;
/**      * 在线开锁。      *      * @param auth 指定授权数据。如果授权数据比较复杂，那么可以是一串JSON字符串，由底层程序来处理这串字符串。      *             强烈建议使用JSON字符串，这样上层应用开发可以完全不用关心授权的具体内。      *      * @param lockCode 指定锁芯ID。      * @param startTime 指定授权开始有效时间。      * @param endTime 指定授权开始失效时间。
 */
-(void)unlock:(NSString*)auth
     lockCode:(NSString*)lockCode
    startTime:(NSDate*)startTime
      endTime:(NSDate*)endTime;
/**      * 把开锁权限转移到蓝牙BLE钥匙。      *      * @param nIndex 指定授权的索引号，即写到哪个位置，1是第一个。      * @param auth 锁的密钥      *      * @param lockCode 指定锁芯ID。      * @param startTime 指定授权开始有效时间。      * @param endTime 指定授权开始失效时间。      * @param offLineTime 指定离线有效时长(单位:小时)，即，手机多长时间不连接钥匙，此授权就要禁止。      *                    如果本参数输入0，那么本授权将使用validityPeriod作为默认的离线时间。
 */
-(void)transferAuth:(int)nIndex
               auth:(NSString*)auth
           lockCode:(NSString*)lockCode
          startTime:(NSDate*)startTime
            endTime:(NSDate*)endTime
        offLineTime:(int)offLineTime;
@end
