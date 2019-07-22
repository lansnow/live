#pragma once
 
#define __VALLEYAPI extern "C"




#ifndef ERR_NOT_INITIALIZE

#define ERR_SUCCEED 0         // �����ɹ�
#define ERR_NOT_LOGINED  -1   // δ��¼�ɹ�       
#define ERR_ALREADY_RUN  -2   // �Ѿ�������   
#define ERR_USER_NOTFOUND -3  // δ�ҵ��û�   
#define ERR_EXCUTING -4		  // ����ִ���� 
#define ERR_NOT_INITIALIZE -5 // δ��ʼ��
#define ERR_UNSUPPORT -6      // ���ܲ�֧��
#define ERR_ARGUMENT  -7	  // ��������

#define ERR_CHANNEL_EXPIRED 1        // Ƶ���Ѿ�ʧЧ
#define ERR_CONNECT_SERVER_FAILED 2  // ���ӷ�����ʧ��
#define ERR_REQUEST_TIMEOUT 3  // ����ʱ
#define ERR_CONFIG 4  // ������Ϣ����   
#define ERR_NET_POOL 5  // ���粻��
#define ERR_VERSION_UNSUPPORTED 6  // �汾��֧��
#define ERR_AUTHO_FAILED 7  // ��Ȩʧ�� 
#define ERR_NOT_ENOUGH_CHANNEL 8  // Ƶ����Դ����
#define ERR_SERVER_ERROR 9  // ����������
#define ERR_OPEN_RECORD 10  // �򿪲ɼ�ʧ��
#define ERR_OPEN_PLAYOUT 11  // �򿪲���ʧ��
#define ERR_RECORD_PERMISSION 12  // û��¼��Ȩ��

#define ERR_CONNECT_CLOSED 20  // ���ӷ�����ʧ��
#define ERR_DATA_LENGHT 21  // ���ݰ����ȳ�������
#define ERR_SENDBUFFER_FULL 22  // ���ͻ��������

#define ERR_UNDEFINED 100  // δ�������

#define IID_USERS		  0x01 
#define IID_AUDIO		  0x02 
#define IID_AUDIOSYSTEM   0x04 
#define IID_AUDIOCTRL     0x08 
#define IID_RTCMSGR		  0x10 

#define RESERVE_CHANNEL_ATTR_CONFIG "##INNER##CHANNEL_SATTR_CONFIG"  //���÷����ڲ����ԣ��������������ڲ�������

enum
{
    STATUS_NONE = 0,     // δ��¼
    STATUS_LOGINING = 1, // ��¼��
    STATUS_LOGINED  = 2, // �Ѿ���¼
};

enum msgtype
{
    typeText = 1,         // �ı���Ϣ, SDK������Ϣԭʼ���ݣ�ֻ�ǽ������ƽ̨ͳһ����utf8��ʽ���Ա������SDK��˫����ͳһ�γ�����
    typeAudio = 2,         // ������Ϣ
    typeBinary = 3,      // ��������Ϣ
    typeCmd = 10,         // ������Ϣ�����ڷ������ϴ洢������ת��
};

enum AUDIOCTRL{  
	typeAec = 0x04,    //�������ƿ���
	typeNs = 0x08,     //�������ƿ���
	typeAgc = 0x010,   //�Զ��������
	typeVad = 0x020,   //���������� 
//	typeEcho = 0x40,   //�������� 
	typeMusicMode = 0x1000 // ���ַ�����ƽӿڣ��������typeMusicMode����Ϊ���ַ������Ч 
};


enum eRealtimeDataType
{
	data_unsafe_data = 0,    // ��ͨ���������� �ɶ���
//	data_safe_data = 1,      // ��ͨ���������� ���ɶ��� 
	data_video_keyframe = 5, // ��Ƶ�ؼ�֡  
	data_video_frame = 6,    // ��Ƶ��ͨ�м�֡
	data_audio_data = 8,     // �������ݰ� 
};
 

#endif //ERR_NOT_INITIALIZE


#ifndef VIDEO_CAPTURE_TYPE_16X9  
#define VIDEO_CAPTURE_TYPE_16X9         ( 0x000 ) 
// Image resolution
#define VIDEO_SIZE_160                  ( 1 )
#define VIDEO_SIZE_320                  ( 2 )
#define VIDEO_SIZE_480                  ( 3 )
#define VIDEO_SIZE_640                  ( 4 )
#define VIDEO_SIZE_800                  ( 5 )
#define VIDEO_SIZE_960                  ( 6 )
#define VIDEO_SIZE_1280                 ( 8 )
#define VIDEO_SIZE_1920                 ( 0xf ) 

#define VIDEO_CAPTURE_TYPE_16X9_160     ( VIDEO_CAPTURE_TYPE_16X9+VIDEO_SIZE_160 )   // 160*120
#define VIDEO_CAPTURE_TYPE_16X9_320     ( VIDEO_CAPTURE_TYPE_16X9+VIDEO_SIZE_320 )
#define VIDEO_CAPTURE_TYPE_16X9_480     ( VIDEO_CAPTURE_TYPE_16X9+VIDEO_SIZE_480 )
#define VIDEO_CAPTURE_TYPE_16X9_640     ( VIDEO_CAPTURE_TYPE_16X9+VIDEO_SIZE_640 )
#define VIDEO_CAPTURE_TYPE_16X9_800     ( VIDEO_CAPTURE_TYPE_16X9+VIDEO_SIZE_800 )
#define VIDEO_CAPTURE_TYPE_16X9_960     ( VIDEO_CAPTURE_TYPE_16X9+VIDEO_SIZE_960 )
#define VIDEO_CAPTURE_TYPE_16X9_1280    ( VIDEO_CAPTURE_TYPE_16X9+VIDEO_SIZE_1280 )   // 720P 1280*720
#define VIDEO_CAPTURE_TYPE_16X9_1920    ( VIDEO_CAPTURE_TYPE_16X9+VIDEO_SIZE_1920 )   // 1080P
 
#define VIDEO_CAPTURE_TYPE_4X3          ( 0x100 )
#define VIDEO_CAPTURE_TYPE_4X3_160      ( VIDEO_CAPTURE_TYPE_4X3+VIDEO_SIZE_160 )   // 160*120
#define VIDEO_CAPTURE_TYPE_4X3_320      ( VIDEO_CAPTURE_TYPE_4X3+VIDEO_SIZE_320 )
#define VIDEO_CAPTURE_TYPE_4X3_480      ( VIDEO_CAPTURE_TYPE_4X3+VIDEO_SIZE_480 )
#define VIDEO_CAPTURE_TYPE_4X3_640      ( VIDEO_CAPTURE_TYPE_4X3+VIDEO_SIZE_640 )
#define VIDEO_CAPTURE_TYPE_4X3_800      ( VIDEO_CAPTURE_TYPE_4X3+VIDEO_SIZE_800 )
#define VIDEO_CAPTURE_TYPE_4X3_960      ( VIDEO_CAPTURE_TYPE_4X3+VIDEO_SIZE_960 )
#define VIDEO_CAPTURE_TYPE_4X3_1280     ( VIDEO_CAPTURE_TYPE_4X3+VIDEO_SIZE_1280 )   // 1280*720
#define VIDEO_CAPTURE_TYPE_4X3_1920     ( VIDEO_CAPTURE_TYPE_4X3+VIDEO_SIZE_1920 )   // 1280*720

#define VIDEO_CAPTURE_TYPE_16X16        ( 0x200 )  
#define NO_ROTATE_TYPE_90               ( 1 )

#define VIDEO_FRAME_COUNT_5				( 0x1000 )
#define VIDEO_FRAME_COUNT_8				( 0x2000 )
#define VIDEO_FRAME_COUNT_10			( 0x3000 )
#define VIDEO_FRAME_COUNT_15			( 0x4000 )  // default
#define VIDEO_FRAME_COUNT_20			( 0x5000 )
#define VIDEO_FRAME_COUNT_24			( 0x7000 )
#define VIDEO_FRAME_COUNT_30			( 0x9000 )

#endif //VIDEO_CAPTURE_TYPE_16X9
 
#define CAMERA_INDEX_FRONT  -1 //[DFT]  //windows [DFT] >= 0 windows
#define CAMERA_INDEX_BACK   -2
#define CAMERA_INDEX_SWITCH -3  //�ƶ��ˣ�-3 �л��� windows -3 �������

typedef void* handle_t;
typedef void* hobj_t; 
typedef void* hevt_t;
typedef long long seond_t;

#ifdef _IOS
#import <UIKit/UIKit.h>
    struct VideoWnd{
        UIView* view;
        int renderMode;
        int mirrorMode;
    };
    typedef VideoWnd* hvideo_t;
#else
    typedef void* hvideo_t;
#endif


enum eLocalAttr
{
	attr_audio_volume = 101,         //����������С
	attr_audio_enable_apm = 102,     // 
	attr_audio_disable_apm = 103,
	attr_audio_record_device = 105,
	attr_audio_playout_device = 106,

	attr_servers_config = 200,      // ��������
};


 

enum EVTID
{
	RTC_EVTID_RESP_FROM = 0,
	RTC_EVTID_RESP_LOGINED = (RTC_EVTID_RESP_FROM + 1),    //��Ӧ�¼� �յ��û���¼�ɹ���ʧ�ܵ�Ӧ�� objRespLogin
	RTC_EVTID_RESP_SET_CHANNEL_ATTR = (RTC_EVTID_RESP_FROM + 3),  //��Ӧ�¼� �յ�����Ϣ�ɹ���ʧ�ܵ�Ӧ�� objRespSetChannelAttr 
	RTC_EVTID_RESP_SET_USER_ATTR = (RTC_EVTID_RESP_FROM + 4),  //��Ӧ�¼� �յ�����Ϣ�ɹ���ʧ�ܵ�Ӧ�� objRespSetUserAttr 

	RTC_EVTID_RESP_SEND_MSG = (RTC_EVTID_RESP_FROM + 50),  //��Ӧ�¼� �յ�����Ϣ�ɹ���ʧ�ܵ�Ӧ�� objRespMsg 

	RTC_EVTID_RESP_RECORD = (RTC_EVTID_RESP_FROM + 100),  //¼������ objRespRecord 

	RTC_EVTID_NTF_FROM = 1000,
	RTC_EVTID_NTF_USER_ENTER = (RTC_EVTID_NTF_FROM + 1),   //֪ͨ�¼� �յ��û����뷿�� objNtfUserEnter
	RTC_EVTID_NTF_USER_LEAVE = (RTC_EVTID_NTF_FROM + 2),   //֪ͨ�¼� �յ��û��뿪���� objNtfUserLeave

	RTC_EVTID_NTF_SET_CHANNEL_ATTR = (RTC_EVTID_NTF_FROM + 3),  //֪ͨ�¼� �յ����÷������Ե�֪ͨ objNtfSetChannelAttr 
	RTC_EVTID_NTF_SET_USER_ATTR = (RTC_EVTID_NTF_FROM + 4),  //֪ͨ�¼� �յ������û����Ե�֪ͨ objNtfSetUserAttr 
	RTC_EVTID_NTF_USER_SPEAK_CHANGED = (RTC_EVTID_NTF_FROM + 5),  //֪ͨ�¼� �յ������û����Ե�֪ͨ objNtfUserSpeakChanged 
 
	RTC_EVTID_NTF_RECV_MSG = (RTC_EVTID_NTF_FROM + 50),  //֪ͨ�¼� �յ��û���������Ϣ objNtfMsg
	RTC_EVTID_NTF_RECV_REALTIME_DATA = (RTC_EVTID_NTF_FROM + 55),  //֪ͨ�¼� �յ��û���������Ϣ objNtfData_keys
 	RTC_EVTID_NTF_CONNECT_LOST = (RTC_EVTID_NTF_FROM + 80),    //֪ͨ�¼� �յ�����Ͽ�����Ϣ objNtfNetLost
	RTC_EVTID_NTF_CONNECT_RESUME = (RTC_EVTID_NTF_FROM + 81),  //֪ͨ�¼� �յ������������ϵ���Ϣ objNtfNetResume
	RTC_EVTID_NTF_DUP_LOGINED = (RTC_EVTID_NTF_FROM + 82), //֪ͨ�¼� �յ��˺���ص�¼����Ϣ objNtfDupLogined

	RTC_EVTID_NTF_RECORD_END = (RTC_EVTID_NTF_FROM + 100),  //¼�����֪ͨ objNtfRecordEnd 
};
 
enum objBaseEvent_keys
{
	objBaseEvent_evtid = 0,
};
 
 
// ��Ӧ�¼�����Ӧ�¼����������룬ec=0��ʶ�ɹ���ec!=0��ʶʧ�ܣ�����ʧ�ܼ���������
enum objRespEvent_keys // objBaseEvent_keys
{ 
	objRespEvent_ecode = 1, 
};

// ֪ͨ�¼�
typedef objBaseEvent_keys objNtfEvent_keys;



enum objString_keys
{
	objStringValue = 10,
};



enum object_channel_attr_keys
{
	objChannelAttrName  = 10,
	objChannelAttrValue = 11,
};


enum object_user_attr_keys
{
	objUserAttrUserID = 10,
	objUserAttrName   = 11,
	objUserAttrValue   = 12,
};



enum objUserItem_keys
{
	objUserID      = 10, 
	//attrs
};


//��Ӧ�¼� �յ��û���¼�ɹ���ʧ�ܵ�Ӧ��
enum objRespLogin_keys // : objRespEvent_keys
{
	objRespLogin_userid    = 10, 
};


//֪ͨ�¼� �յ��û����뷿��
enum objNtfUserEnter_keys //: objBaseEvent_keys
{
	objNtfUserEnter_userid = 10,
};



//֪ͨ�¼� �յ��û��뿪����
enum objNtfUserLeave_keys // : objBaseEvent_keys
{
	objNtfUserLeave_userid = 10,
};


enum objRespSetChannelAttr_keys // : objRespEvent_keys
{
	 //object_channel_attr_keys
};


enum objRespSetUserAttr_keys // : objBaseEvent
{
	//object_channel_attr_keys
};


enum objNtfSetUserAttr_keys // : objBaseEvent
{
	//object_channel_attr_keys
};


 
//��Ӧ�¼� �յ�����Ϣ�ɹ���ʧ�ܵ�Ӧ��
enum objMsgItem_keys
{
	objMsg_fromuserid = 10,
	objMsg_touserid   = 11,
	objMsg_msgdata    = 12,
	objMsg_msglen     = 13,
	objMsg_token      = 14,
	objMsg_msgtype    = 15,
	objMsg_msgtime    = 16,
};


enum objRespMsg_keys // : objRespEvent_keys
{ 
	//objMsgItem
};

//֪ͨ�¼� �յ��û���������Ϣ objNtfMsg
enum objNtfMsg_keys // : objNtfEvent_keys
{
	//objMsgItem
};
 
 
//֪ͨ�¼� �յ�����Ͽ�����Ϣ
enum objNtfNetLost_keys{}; // : objNtfEvent_keys

//֪ͨ�¼� �յ������������ϵ���Ϣ
enum objNtfNetResume_keys{};// : objNtfEvent_keys

//֪ͨ�¼� �յ��˺���ص�¼����Ϣ
enum objNtfDupLogined_keys{}; // : objNtfEvent_keys


enum objRespRecord  //objRespEvent_keys
{
	objRespRecord_userid = 10,
};


enum objNtfRecordEnd //objNtfEvent_keys
{
	objNtfRecord_userid = 10,
	objNtfRecord_FileSize = 11,
};
 

//֪ͨ�¼� �յ��û��뿪����
enum objNtfData_keys // : objBaseEvent_keys
{
	objData_Userid = 10,
	objData_buffer = 11,
	objData_len = 12,
	objData_type = 13,
};

enum objNtfUserSpeakChanged// : objBaseEvent_keys
{
	objNtfSpeaking_Userid = 10,
	objNtfSpeaking_SpeakFlag = 11, 
};


__VALLEYAPI bool         Valley_InitSDK(const char* workfolder, const char* localconfig); //��ʼ��SDK,һ������ֻ��Ҫ��ʼ��һ��
__VALLEYAPI void         Valley_CleanSDK();       //��ʼ��SDK,һ������ֻ��Ҫ��ʼ��һ��
__VALLEYAPI const char*	 Valley_GetSDKVersion();  //��ȡSDK�汾
__VALLEYAPI const char*	 Valley_GetErrDesc(int ec);     //��ȡ�������Ӧ������
__VALLEYAPI void     	 Valley_SetAuthKey(const char* authkey);     //������Ȩ��


__VALLEYAPI handle_t     Valley_CreateChannel(bool withVideo);  //����һ�����䣬�Ƿ���Ҫ֧����Ƶ
__VALLEYAPI void         Valley_Release(handle_t s);  //����һ������

__VALLEYAPI int          Valley_EnableInterface(handle_t s, int iids);  //���������Ч

__VALLEYAPI hevt_t       Valley_GetEvent(handle_t s);           //��ȡ�¼�����֧�֣�����������û���¼����ؿ�֧�֣����¼������¼��ṹ֧�֣���Ҫ����Valley_ReleaseEvent�ͷ��¼�����ָ��
__VALLEYAPI int          Valley_GetEventIntAttr(hevt_t he, int attrid);  //��ȡ�¼����ԣ��������Σ�
__VALLEYAPI const char*  Valley_GetEventAttr(hevt_t he, int attrid);  //��ȡ�¼����ԣ������ַ�����
__VALLEYAPI void         Valley_ReleaseEvent(hevt_t he);  //�ͷ��¼�����ָ��

  
__VALLEYAPI int          Valley_Login(handle_t s, const char* channelid, const char* userid); //��¼����
__VALLEYAPI void         Valley_Logout(handle_t s);        //�˳�����
__VALLEYAPI int          Valley_GetLoginStatus(handle_t s);  //��ȡ��¼״̬

__VALLEYAPI int          Valley_SetChannelAttr(handle_t s, const char* name, const char* value);  // ���÷�������
__VALLEYAPI int          Valley_SendMsgr(handle_t s, int msgtype, const char* data, int len, const char* token, const char* toUserID);  // ������Ϣ

__VALLEYAPI int			 Valley_SendRealtimeData(handle_t s, int datatype, const void* data, int dlen); //datatype�ο�eRealtimeDataType

__VALLEYAPI int          Valley_SetVideoProfile(handle_t s, int profile);   // ���ñ�����Ƶ����


__VALLEYAPI int          Valley_SetLocalVideo(handle_t s, hvideo_t hVideo);   // ���ñ�����Ƶ��ʾ����
__VALLEYAPI int          Valley_RemoveLocalVideo(handle_t s);   // �رձ�����Ƶ��ʾ

__VALLEYAPI int          Valley_SetUserVideo(handle_t s, const char* userid, hvideo_t hVideo);  // �����û���Ƶ��ʾ����
__VALLEYAPI int          Valley_RemoveUserVideo(handle_t s, const char* userid);  // �ر��û���Ƶ��ʾ

__VALLEYAPI int          Valley_EnableLocalAudio(handle_t s, bool bEnable);  // �رջ�� ��������
__VALLEYAPI int          Valley_EnableLocalVideo(handle_t s, bool bEnable);  // �رջ�� ������Ƶ

__VALLEYAPI int          Valley_EnableRemoteAudio(handle_t s, const char* userid, bool bEnable); // �رջ���û�����
__VALLEYAPI int          Valley_EnableRemoteVideo(handle_t s, const char* userid, bool bEnable); // �رջ���û���Ƶ  

__VALLEYAPI int          Valley_DisableAudio(handle_t s, bool bDisabled); // ����֧��������Ĭ��֧��, ��Ƶ����ֻ���ڵ�¼ǰ����һ�Σ�������Ч
__VALLEYAPI int          Valley_DisableVideo(handle_t s); // ����֧����Ƶ��Ĭ��֧��, ֻ���ڵ�¼ǰ����һ�Σ�������Ч
 
__VALLEYAPI int          Valley_SetCameraIndex(handle_t s, int index); // ��������ͷ
__VALLEYAPI int          Valley_SetSpeakOn(handle_t s, int index);     // ����������Ͳ�л� -1 ���������� 0 ��Ͳ 1 ������ ������-1��0֮���л�


//¼�ƹ���
__VALLEYAPI int          Valley_StartRecord(handle_t s, const char* uid, const char * pszFileName, int uMaxTime);
__VALLEYAPI int          Valley_StopRecord(handle_t s, const char* uid);

//��Ϣ����֧�� 
__VALLEYAPI int          Valley_SetChannelAttr(handle_t s, const char* name, const char* value);  // ���÷�������
__VALLEYAPI hobj_t       Valley_GetChannelAttr(handle_t s, const char* name);  //objString_keys  // ��ȡ��������

//���÷��䱾������
__VALLEYAPI int          Valley_SetLocalAttrValue(handle_t s, eLocalAttr name, const char* value); // ���ñ������� 

__VALLEYAPI int          Valley_SetUserAttr(handle_t s, const char* uid, const char* name, const char* value); // �����û�����
__VALLEYAPI hobj_t       Valley_GetUserAttr(handle_t s, const char* uid, const char* name); //objString_keys  // ��ȡ�û�����

 
__VALLEYAPI hobj_t       Valley_GetUser(handle_t s, const char* uid); // ��ȡ�û�
__VALLEYAPI hobj_t       Valley_GetUserList(handle_t hobj);  // ��ȡ�û��б�
__VALLEYAPI int          Valley_GetListCount(hobj_t hobj);   // ��ȡ�б�Ԫ�ظ���
__VALLEYAPI bool         Valley_NextItem(hobj_t hobj);       // �ƶ���ǰ�б���ǰԪ��λ��
 
__VALLEYAPI int          Valley_GetObjectIntAttr(hobj_t hobj, int attrid);  // ��ȡ�������ԣ��б�Ϊ��ǰԪ������
__VALLEYAPI const char*  Valley_GetObjectAttr(hobj_t hobj, int attrid); // ��ȡ�������ԣ��б�Ϊ��ǰԪ������
__VALLEYAPI const char*  Valley_GetObjectNameAttr(hobj_t hobj, const char* name);  // ��ȡ�������ԣ��б�Ϊ��ǰԪ������
__VALLEYAPI void         Valley_ReleaseObject(hobj_t hobj);  // �ͷŶ������л�ȡ�� Ϊ hobj_t �Ķ��󣬶���Ҫͨ���˺����ͷ��ڴ�
 

//�����Ǽ򵥵��õ����ӣ���¼���������䣬һ������IM���ܣ�������������Ϣ�����Է��û�����ʲô�ģ�һ��������������Ƶͨ��
 
/*
  1) ��ʼ��SDK
  const char* localconfig = "<?xml version=\"1.0\" encoding=\"utf-8\"?><root><localversion>1</localversion></root>";
  localconfig���ñ�ʾ֧�ֱ���ͨ��
  Valley_InitSDK("d:\\workfolder\", localconfig);

  handle_t channelim    = Valley_CreateChannel(false);   // ����һ�����䣬��֧����Ƶ������imͨ��
  handle_t channelvideo = Valley_CreateChannel(true);    // ����һ�����䣬֧����Ƶ����������Ƶͨ�� 


  Valley_EnableInterface(channelim, IID_RTCMSGR);  //IM���䣬ֻ��Ҫ֧����Ϣ����


  2����¼IM���� 
  const char* localimserver = "<?xml version=\"1.0\" encoding=\"utf-8\"?><root><mcu><channel>s-10.80.64.56:8002</channel></mcu></root>";
  Valley_SetChannelAttr(RESERVE_CHANNEL_ATTR_CONFIG, localimserver);
  Valley_Login(channelim, ��98��, "123"); 

  3����¼��Ƶ����  
  Valley_SetLocalVideo(channelvideo, m_hMyWnd); //���ñ�����Ƶ����
  Valley_SetVideoProfile(channelvideo, VIDEO_CAPTURE_TYPE_4X3_640); //���ñ�����Ƶ��С
  Valley_Login(channelvideo, ��225��, "123");


  4�� ��ʱȡ������������¼�������
  void ontimer()
  {
      // ����IM������Ϣ
      while(true)
	  {
         hevt_t e = Valley_GetEvent(channelim);
		 if(NULL == e)
		    break;

		  int evtid = Valley_GetEventIntAttr(e, objBaseEvent_evtid);
		  if(evttype > RTC_EVTID_NTF_FROM) 
		     process_im_notify_event(e); 
		  else 
		      process_im_resp_event(e);

		  Valley_ReleaseEvent(e);
	  }
	  
	  // ��������Ƶ������Ϣ
	  while(true)
	  {
		 hevt_t e = Valley_GetEvent(channelvideo);
		 if(NULL == he)
			  break;

		 int evtid = Valley_GetEventIntAttr(e, objBaseEvent_evtid);
		 if(evttype > RTC_EVTID_NTF_FROM)
			  process_av_notify_event(e);
		 else
			  process_av_resp_event(e);

		  Valley_ReleaseEvent(e);
	  } 
  }


  5�����䲻���ˣ��˳�����
  Valley_Logout(channelim);
  Valley_Logout(channelvideo);

  6�� ���ٷ������
  Valley_Release(channelvideo);  
  channelvideo = NULL;


  Valley_Release(channelim);
  channelim = NULL;

  7) �˳����̣��ͷ�SDK
  Valley_CleanSDK();
  */