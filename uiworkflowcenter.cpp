#include "uiworkflowcenter.h"
#include "QThread"




UIWorkflowCenter::UIWorkflowCenter(UISerial0* serial,UISerial1* serial1,QObject *parent) :
    QObject(parent),m_Serial(serial),m_Serial1(serial1)
{
    serialFilter=m_Serial->GetSerialFilter();
    serialSender=m_Serial->GetSerialSender();

    serialFilter1=m_Serial1->GetSerialFilter1();
    serialSender1=m_Serial1->GetSerialSender1();

    m_DeviceControl = new DeviceControl();

    connect(
                serialFilter,
                SIGNAL(Serial1TestInsReceived(type_BaseInstruction* )),
                this,SLOT(On_Serial1TestInsReceived(type_BaseInstruction* ))
                );

    connect(
                serialFilter1,
                SIGNAL(PrintSerialInsReceived(type_BaseInstruction* )),
                this,SLOT(On_PrintSerialInsReceived(type_BaseInstruction* ))
                );

    connect(
                serialFilter,
                SIGNAL(UsbTestInsReceived(type_BaseInstruction* )),
                this,SLOT(On_UsbTestInsReceived(type_BaseInstruction* ))
                );

    connect(
                serialFilter,
                SIGNAL(LightTestInsReceived(type_BaseInstruction* )),
                this,SLOT(On_LightTestInsReceived(type_BaseInstruction* ))
                );

    connect(
                serialFilter,
                SIGNAL(BuzzerTestInsReceived(type_BaseInstruction* )),
                this,SLOT(On_BuzzerTestInsReceived(type_BaseInstruction* ))
                );

   //yzz

    connect(
                serialFilter,
                SIGNAL(RtcTestInsReceived(type_BaseInstruction* )),
                this,SLOT(On_RtcTestInsReceived(type_BaseInstruction* ))
                );
    connect(
                serialFilter,
                SIGNAL(LedTestInsReceived(type_BaseInstruction* )),
                this,SLOT(On_LedTestInsReceived(type_BaseInstruction* ))
                );

    connect(
                serialFilter,
                SIGNAL(clearTestInsReceived(type_BaseInstruction* )),
                this,SLOT(On_clearTestInsReceived(type_BaseInstruction* ))
                );


}




void UIWorkflowCenter::On_PrintSerialInsReceived(type_BaseInstruction* Serial1TestIns)
{
    type_BaseInstruction Serial3TestInsACK;

    Serial3TestInsACK.s_FrameHeader=FRAME_HEADER;
    Serial3TestInsACK.s_FrameSign=FRAME_SIGN_ARM;
    Serial3TestInsACK.s_FrameLength=FRAME_LENGTH;
    Serial3TestInsACK.s_InsCode=0xA1;
    Serial3TestInsACK.s_InsData=0x00;
    Serial3TestInsACK.s_FrameReserved1=0x00;
    Serial3TestInsACK.s_FrameReserved2=0x00;
    Serial3TestInsACK.s_VerifyValue=FRAME_VERIFY_DEFAULT;
    Serial3TestInsACK.s_FrameTrail=FRAME_TRAIL;

    serialSender1->SendInsACK(&Serial3TestInsACK);
    return;
}
void UIWorkflowCenter::On_Serial1TestInsReceived(type_BaseInstruction* Serial1TestIns)
{
    type_BaseInstruction Serial1TestInsACK;

    Serial1TestInsACK.s_FrameHeader=FRAME_HEADER;
    Serial1TestInsACK.s_FrameSign=FRAME_SIGN_ARM;
    Serial1TestInsACK.s_FrameLength=FRAME_LENGTH;
    Serial1TestInsACK.s_InsCode=0xA0;
    Serial1TestInsACK.s_InsData=0x00;
    Serial1TestInsACK.s_FrameReserved1=0x00;
    Serial1TestInsACK.s_FrameReserved2=0x00;
    Serial1TestInsACK.s_VerifyValue=FRAME_VERIFY_DEFAULT;
    Serial1TestInsACK.s_FrameTrail=FRAME_TRAIL;

    serialSender->SendInsACK(&Serial1TestInsACK);
}


void UIWorkflowCenter::On_LightTestInsReceived(type_BaseInstruction* LightTestIns)
{
    type_BaseInstruction LightTestInsACK;

    LightTestInsACK.s_FrameHeader=FRAME_HEADER;
    LightTestInsACK.s_FrameSign=FRAME_SIGN_ARM;
    LightTestInsACK.s_FrameLength=FRAME_LENGTH;
    LightTestInsACK.s_InsCode=0xA3;
    LightTestInsACK.s_InsData=0x00;
    LightTestInsACK.s_FrameReserved1=0x00;
    LightTestInsACK.s_FrameReserved2=0x00;
    LightTestInsACK.s_VerifyValue=FRAME_VERIFY_DEFAULT;
    LightTestInsACK.s_FrameTrail=FRAME_TRAIL;

    serialSender->SendInsACK(&LightTestInsACK);

    m_DeviceControl->led_control();

}
void UIWorkflowCenter::On_BuzzerTestInsReceived(type_BaseInstruction* BuzzerTestIns)
{
    type_BaseInstruction BuzzerTestInsACK;

    BuzzerTestInsACK.s_FrameHeader=FRAME_HEADER;
    BuzzerTestInsACK.s_FrameSign=FRAME_SIGN_ARM;
    BuzzerTestInsACK.s_FrameLength=FRAME_LENGTH;
    BuzzerTestInsACK.s_InsCode=0xA4;
    BuzzerTestInsACK.s_InsData=0x00;
    BuzzerTestInsACK.s_FrameReserved1=0x00;
    BuzzerTestInsACK.s_FrameReserved2=0x00;
    BuzzerTestInsACK.s_VerifyValue=FRAME_VERIFY_DEFAULT;
    BuzzerTestInsACK.s_FrameTrail=FRAME_TRAIL;

    serialSender->SendInsACK(&BuzzerTestInsACK);
    m_DeviceControl->up_beer_control(3);

}
void UIWorkflowCenter::On_LedTestInsReceived(type_BaseInstruction* LedTestIns)
{
    type_BaseInstruction LedTestInsACK;

    LedTestInsACK.s_FrameHeader=FRAME_HEADER;
    LedTestInsACK.s_FrameSign=FRAME_SIGN_ARM;
    LedTestInsACK.s_FrameLength=FRAME_LENGTH;
    LedTestInsACK.s_InsCode=0xA9;
    LedTestInsACK.s_InsData=0x00;
    LedTestInsACK.s_FrameReserved1=0x00;
    LedTestInsACK.s_FrameReserved2=0x00;
    LedTestInsACK.s_VerifyValue=FRAME_VERIFY_DEFAULT;
    LedTestInsACK.s_FrameTrail=FRAME_TRAIL;

    serialSender->SendInsACK(&LedTestInsACK);
}

void UIWorkflowCenter::On_UsbTestInsReceived(type_BaseInstruction* UsbTestIns)
{
    //USB1
    type_BaseInstruction Usb1TestInsACK;

    Usb1TestInsACK.s_FrameHeader=FRAME_HEADER;
    Usb1TestInsACK.s_FrameSign=FRAME_SIGN_ARM;
    Usb1TestInsACK.s_FrameLength=FRAME_LENGTH;
    Usb1TestInsACK.s_InsCode=0xA2;

    QString dir1= "/media/sda1";
    QString dir2= "/media/sdb1";
    QString dir3= "/media/sdc1";

    if(QFile::exists(dir1))
        Usb1TestInsACK.s_InsData=0x01;
    else
         Usb1TestInsACK.s_InsData=0x00;

    if(QFile::exists(dir2))
         Usb1TestInsACK.s_FrameReserved1=0x01;
    else
         Usb1TestInsACK.s_FrameReserved1=0x00;

    if(QFile::exists(dir3))
        Usb1TestInsACK.s_FrameReserved2=0x01;
    else
       Usb1TestInsACK.s_FrameReserved2=0x00;



    Usb1TestInsACK.s_VerifyValue=FRAME_VERIFY_DEFAULT;
    Usb1TestInsACK.s_FrameTrail=FRAME_TRAIL;

    serialSender->SendInsACK(&Usb1TestInsACK);




}

void UIWorkflowCenter::On_RtcTestInsReceived(type_BaseInstruction* RtcTestIns)
{

    // write time to system
//        int hour   = RtcTestIns->s_InsData;
//        int minute = RtcTestIns->s_FrameReserved1;
//        int second = RtcTestIns->s_FrameReserved2;
//         //系统设置
//         QString szHH= QString("%1").arg(hour,2,10,QLatin1Char('0'));
//         QString szMM=QString("%1").arg(minute,2,10,QLatin1Char('0'));
//         QString szSS=QString("%1").arg(second,2,10,QLatin1Char('0'));
        // QString szTime=QString("%1:%2:%3").arg(szHH).arg(szMM).arg(szSS);   szTime =szTime+"\"";
        // QString szDateTime=QDateTime::currentDateTime().toString("\"yyyy-MM-dd ");


    type_BaseInstruction RtcTestInsACK;

    RtcTestInsACK.s_FrameHeader=FRAME_HEADER;
    RtcTestInsACK.s_FrameSign=FRAME_SIGN_ARM;
    RtcTestInsACK.s_FrameLength=FRAME_LENGTH;
    RtcTestInsACK.s_InsCode=0xA5;
    RtcTestInsACK.s_InsData=0x01;
    RtcTestInsACK.s_FrameReserved1=0x02;
    RtcTestInsACK.s_FrameReserved2=0x03;
    RtcTestInsACK.s_VerifyValue=FRAME_VERIFY_DEFAULT;
    RtcTestInsACK.s_FrameTrail=FRAME_TRAIL;

    serialSender->SendInsACK(&RtcTestInsACK);

}

void UIWorkflowCenter::On_clearTestInsReceived(type_BaseInstruction* clearTestIns)
{
    type_BaseInstruction Serial3TestInsACK;

    Serial3TestInsACK.s_FrameHeader=FRAME_HEADER;
    Serial3TestInsACK.s_FrameSign=FRAME_SIGN_ARM;
    Serial3TestInsACK.s_FrameLength=FRAME_LENGTH;
    Serial3TestInsACK.s_InsCode=0xA8;
    Serial3TestInsACK.s_InsData=0x00;
    Serial3TestInsACK.s_FrameReserved1=0x00;
    Serial3TestInsACK.s_FrameReserved2=0x00;
    Serial3TestInsACK.s_VerifyValue=FRAME_VERIFY_DEFAULT;
    Serial3TestInsACK.s_FrameTrail=FRAME_TRAIL;

    serialSender->SendInsACK(&Serial3TestInsACK);

    // 复制app启动文件 到 /etc/
    // 重启动

    QString clearAPPins="cp /home/root/nbdpTest/profile /etc/ ";
    system(clearAPPins.toLatin1().data());

    QString reStartAPP="reboot";
    system(reStartAPP.toLatin1().data());

}
void UIWorkflowCenter::send_test_start_port()
{
    type_BaseInstruction testStartBack;
    testStartBack.s_FrameHeader    = FRAME_HEADER;
    testStartBack.s_FrameSign      = FRAME_SIGN_ARM;
    testStartBack.s_FrameLength    = FRAME_LENGTH;

    testStartBack.s_InsCode        = FRAME_CODE_STARTTest;

    testStartBack.s_InsData        = 0x00;
    testStartBack.s_FrameReserved1 = 0x00;
    testStartBack.s_FrameReserved2 = 0x00;
    testStartBack.s_VerifyValue    = be16toh(0x011E);
    testStartBack.s_FrameTrail     = 0x16;

    serialSender->SendInsACK(&testStartBack);
    return;
}
