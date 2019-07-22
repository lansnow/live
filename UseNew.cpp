
#define _CRT_SECURE_NO_WARNINGS

/* nuklear - 1.32.0 - public domain */
/*

������ֱ������̨

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <time.h>

//#include "glad/glad.h"
#include"GL/glew.h"
#include"GL/freeglut.h"
#include <GLFW/glfw3.h>

#include "opencv2/opencv.hpp"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include "nuklear.h"
#include "nuklear_glfw_gl3.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024


//�������
#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <map>

#include "GreenScreenRemovalLib.h"
#include "GxIAPI.h"
#include "DxImageProc.h"

#include "ValleyRtcAPI_C.h"
#include <direct.h>

#include "pch.h"

#include <chrono>

#include <fstream>

#if (defined _WIN64)||(defined WIN64) 
#pragma comment(lib, "./lib_win64/ValleyRtcAPI_C.lib")
#else
#pragma comment(lib, "./lib_win32/ValleyRtcAPI_C.lib")
#endif



GX_DEV_HANDLE hDevice = NULL;

// ԭʼͼ������
BYTE *pBufferRaw;

// RGBͼ������
BYTE *pBufferRGB;
// ԭʼͼ��߶�


int64_t nImageHeight;
// ԭʼͼ����
int64_t nImageWidth;

// ���ظ�ʽ = Bayer RG8
int64_t nPixelColorFormat;

// ͼ���С
int64_t nPayLoadSize;
handle_t m_hRoom; // �������

extern GLuint tex;

// �����豸��Ϣ
std::map<uint32_t, char*> deviceInfoMap;

CRITICAL_SECTION gLockMat;


cv::Mat mat;
cv::Mat realMat;
//�������ز���

bool SetConfig = false;
int start = 0;


struct nk_context *ctx;

//��������֧��
bool PushPic = false;

// ��ֵ
int min_green = 10;
int max_green = 10;

int cutwidth = 10;

cv::Mat all_dsc;

// ����
BMPStreamer_web *webStreamer;
// FPS
int fps = 20;
int defrate = 0.7;
//�������
struct tTestHdr
{
	uint32_t seq;
	uint32_t tick;
};

static char text[6][64];
static int text_len[6];

#include "setting_video.c"

tTestHdr* ptembuf = nullptr;
uint8_t *encode_data = nullptr;
int encode_data_size = 0;

cv::Mat bgpic;
cv::Mat bgpic1 = cv::imread("./jpg/bg1.jpg");
cv::Mat bgpic2 = cv::imread("./jpg/bg2.jpg");
cv::Mat bgpic3 = cv::imread("./jpg/bg3.jpg");
cv::Mat bgpic4 = cv::imread("./jpg/bg4.jpg");
cv::Mat bgpic5 = cv::imread("./jpg/bg5.jpg");

int bgindexNum = 1;
cv::VideoCapture cap;
bool showVideo = false;
//���ص�ǰϵͳ�ĺ���ʱ��
std::chrono::milliseconds returntime() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}

static void error_callback(int e, const char *d)
{
	printf("Error %d: %s\n", e, d);
}
int startlisten();
cv::Mat replace_and_blend(cv::Mat &frame, cv::Mat &mask, cv::Mat &bgpic);

//ͼ��ص�������
static void GX_STDC OnFrameCallbackFun(GX_FRAME_CALLBACK_PARAM* pFrame)
{
	if (pFrame->status == GX_FRAME_STATUS_SUCCESS)
	{
		// ����ԭʼ����
		memcpy(pBufferRaw, pFrame->pImgBuf, pFrame->nImgSize);
		// RGBת��
		DxRaw8toRGB24(pBufferRaw, pBufferRGB, (VxUint32)(nImageWidth), (VxUint32)(nImageHeight), RAW2RGB_NEIGHBOUR, DX_PIXEL_COLOR_FILTER(nPixelColorFormat), false);

		EnterCriticalSection(&gLockMat);
		memcpy(mat.data, pBufferRGB, (size_t)(nImageWidth*nImageHeight * 3));
		auto timeNow3 = returntime();
		
		//���㷨
		DGene::GreenScreenRemoval::MattingImage datamat;
		datamat = DGene::GreenScreenRemoval::GreenScreenMatting(mat, 6,min_green, max_green);
		
		switch (bgindexNum)
		{
		case 1:
			cv::resize(bgpic1, bgpic, cv::Size(nImageWidth, nImageHeight), (0, 0), (0, 0), cv::INTER_LINEAR);
			break;
		case 2:
			cv::resize(bgpic2, bgpic, cv::Size(nImageWidth, nImageHeight), (0, 0), (0, 0), cv::INTER_LINEAR);
			break;
		case 3:
			cv::resize(bgpic3, bgpic, cv::Size(nImageWidth, nImageHeight), (0, 0), (0, 0), cv::INTER_LINEAR);
			break;
		case 4:
			cv::resize(bgpic4, bgpic, cv::Size(nImageWidth, nImageHeight), (0, 0), (0, 0), cv::INTER_LINEAR);
			break;

		default:
			cv::resize(bgpic5, bgpic, cv::Size(nImageWidth, nImageHeight), (0, 0), (0, 0), cv::INTER_LINEAR);
			break;
		}

		realMat = replace_and_blend(mat, datamat.img_matting, bgpic);
		
		if (cutwidth > 0) {
			cv::Scalar replace_color = (0, 0, 0);

			std::cout << "cut width:" << cutwidth << std::endl;
			cv::Point tmp[4][4];
			int npt[] = { 4 };
			//��
			//����Ϊʲô�������أ�
			/*tmp[0][0] = cv::Point(0, 0);
			tmp[0][1] = cv::Point(nImageWidth,0);
			tmp[0][2] = cv::Point(nImageWidth, cutwidth);
			tmp[0][3] = cv::Point(0, cutwidth);

			const cv::Point *ppt[1] = { tmp[0] };

			cv::fillPoly(realMat, ppt, npt, 1, replace_color, 0);
			*/
			//cv::Point tmp2[1][3];
			//��
			tmp[1][0] = cv::Point(0, 0);
			tmp[1][1] = cv::Point(cutwidth, 0);
			tmp[1][2] = cv::Point(cutwidth, nImageHeight);
			tmp[1][3] = cv::Point(0, nImageHeight);


			const cv::Point *ppt2[1] = { tmp[1] };
			cv::fillPoly(realMat, ppt2, npt, 1, replace_color, 0);


			//��
			tmp[2][0] = cv::Point((nImageWidth - cutwidth), 0);
			tmp[2][1] = cv::Point(nImageWidth, 0);
			tmp[2][2] = cv::Point(nImageWidth, nImageHeight);
			tmp[2][3] = cv::Point((nImageWidth - cutwidth), nImageHeight);


			//��
			tmp[3][0] = cv::Point(0, (nImageHeight - cutwidth));
			tmp[3][1] = cv::Point(nImageWidth, (nImageHeight - cutwidth));
			tmp[3][2] = cv::Point(nImageWidth, nImageHeight);
			tmp[3][3] = cv::Point(0, nImageWidth);




			const cv::Point *ppt3[1] = { tmp[2] };
			//const cv::Point *ppt4[1] = { tmp[3] };

			cv::fillPoly(realMat, ppt3, npt, 1, replace_color, 0);
			//cv::fillPoly(realMat, ppt4, npt, 1, replace_color, 0);



		}
		

		std::cout << "remove color green use:" << returntime().count() - timeNow3.count() << std::endl;
		LeaveCriticalSection(&gLockMat);
		//�������ݣ�ͬʱ��������
		memcpy(webStreamer->rgb_buf, realMat.data, nImageWidth*nImageHeight * 3);
		webStreamer->encode();
		if (webStreamer->got_picture == 1)
		{
			// ��ʼ��Ҫ���͵����ݰ�
			if (nullptr == ptembuf)
			{
				ptembuf = (tTestHdr*)new char[webStreamer->pkt.size + sizeof(tTestHdr)];
				ptembuf->seq = 0;
			}
			// �������ݵ����ݰ�
			ptembuf->tick = GetTickCount();
			ptembuf->seq = webStreamer->pkt.size;
			memcpy(ptembuf + 1, webStreamer->pkt.data, webStreamer->pkt.size);
			//������
			Valley_SendRealtimeData(m_hRoom, data_video_frame, ptembuf, sizeof(tTestHdr) + webStreamer->pkt.size);
			webStreamer->release_pkt();
			if (ptembuf != nullptr)
			{
				delete[] ptembuf;
				ptembuf = nullptr;
			}
		}
	}

}


cv::Mat replace_and_blend(cv::Mat &frame, cv::Mat &mask, cv::Mat &bgpic)
{
	//background color
	//int r1 = 255, g1 = 255, b1 = 255;

	//����һ�Ž��ͼ  
	cv::Mat result = cv::Mat(frame.size(), frame.type(), cv::Scalar(0, 0, 0));
	//the white background
	//cv::Mat result = cv::Mat(frame.size(), frame.type(), cv::Scalar(b1, g1, r1));
	//ͼ��ĸ� �� ��ͨ����  
	int height = result.rows;
	int width = result.cols;

	// replace and blend  
	int m = 0;//mask������ֵ  
	double wt = 0;//�ںϵı���  

	int r = 0, g = 0, b = 0;//���������  
	int r1 = 0, g1 = 0, b1 = 0;
	int r2 = 0, g2 = 0, b2 = 0;

	//cv::Mat background = cv::Mat(frame.size(), frame.type(), cv::Scalar(0, 0, 0));

	int mask_i = 0;
	for (int i = 0; i < height; i++)
	{
		//����ÿһ�� ÿһ֡ͼ���ָ�룬maskͼ���ָ�룬���ű���ͼ��ָ��,���ͼ��ָ��  
		uchar *pbg = bgpic.ptr<uchar>(i);
		uchar *pframe = frame.ptr<uchar>(i);
		uchar *presult = result.ptr<uchar>(i);

		//if (i >= maxRect.y && i < maxRect.y + maxRect.height) {
			uchar *pmask = mask.ptr<uchar>(mask_i);
			mask_i++;
			for (int j = 0; j < width; j++)
			{
				//if (j >= maxRect.x && j < maxRect.x + maxRect.width) {
					m = *pmask++;//��ȡmask������ֵ  
					if (m == 0)//����Ǳ����Ļ�  
					{
						//��������ͨ���ĸ�ֵ  
						*presult++ = *pbg++;
						*presult++ = *pbg++;
						*presult++ = *pbg++;
						//presult += 3;
						pframe += 3;//��frame��ͼ������ص�ͨ��Ҳ�ƶ���������һ��  
					}
					else if (m == 255)//�����ǰ���Ļ�  
					{
						//��������ͨ���ĸ�ֵ  
						*presult++ = *pframe++;
						*presult++ = *pframe++;
						*presult++ = *pframe++;
						pbg += 3;//��frame��ͼ������ص�ͨ��Ҳ�ƶ���������һ��  
					}
					else
					{
						//����ͼÿ�����ص�����ͨ��  
						b1 = *pbg++;
						g1 = *pbg++;
						r1 = *pbg++;

						//ÿһ֡ÿһ�����ص�����ͨ��  
						b2 = *pframe++;
						g2 = *pframe++;
						r2 = *pframe++;

						// Ȩ��  
						wt = 1.0 - m / 255.0;

						// ���  
						b = b1 * wt + b2 * (1.0 - wt);
						g = g1 * wt + g2 * (1.0 - wt);
						r = r1 * wt + r2 * (1.0 - wt);
						/*b = b2 * (1.0 - wt);
						g = g2 * (1.0 - wt);
						r = r2 * (1.0 - wt);*/

						*presult++ = b;
						*presult++ = g;
						*presult++ = r;
					}
				//}
				//else
				//{
				//	/**presult++ = *pbg++;
				//	*presult++ = *pbg++;
				//	*presult++ = *pbg++;*/
				//	presult += 3;
				//	pframe += 3;//��frame��ͼ������ص�ͨ��Ҳ�ƶ���������һ��  
				//}
			}
		//}
		/*else {
		for (int j = 0; j < width; j++) {
		*presult++ = *pbg++;
		*presult++ = *pbg++;
		*presult++ = *pbg++;
		}
		}*/
	}
	return result;
}


//ȫ������ѡ��
LPTSTR def_name = new char[64];
LPTSTR def_pwd = new char[64];

LPTSTR def_serverip = new char[64];//Զ�̷�����IP
LPTSTR def_videorate = new char[64];//��Ƶ����
LPTSTR def_minsize = new char[64];//��Ļ��С����
LPTSTR def_maxsize = new char[64];//��Ļ������



static char buffer[64];
void initconfig() {

	LPTSTR lpPath = new char[MAX_PATH];
	strcpy(lpPath, ".//defautl_config.ini");
	GetPrivateProfileString("User", "name", "", def_name, 64, lpPath);
	GetPrivateProfileString("User", "passwd", "", def_pwd, 64, lpPath);
	std::string s_name(def_name);
	std::string s_pwd(def_pwd);
	if (s_name != "" && s_pwd != "") {
		//�û�����ʼ��
		memcpy(text[0], def_name, sizeof(def_name));
		text_len[0] = sizeof(def_name) - 1;
		//��ʷ�����¼
		memcpy(buffer, def_pwd, sizeof(def_pwd));
		text_len[1] = sizeof(def_pwd) - 1;
	}

	//�����������
	GetPrivateProfileString("Server", "ip", "", def_serverip, 64, lpPath);
	memcpy(text[3], def_serverip, sizeof(def_serverip));
	text_len[3] = strlen(def_serverip);

	GetPrivateProfileInt("Filter", "min", 0, lpPath);
	memcpy(text[4], def_minsize, sizeof(def_minsize));
	text_len[4] = strlen(def_minsize);

	GetPrivateProfileInt("Filter", "max", 0, lpPath);
	memcpy(text[5], def_maxsize, sizeof(def_maxsize));
	text_len[5] = strlen(def_maxsize);


	GetPrivateProfileString("Video", "rate", "", def_videorate, 64, lpPath);
	memcpy(text[6], def_videorate, sizeof(def_videorate));
	text_len[6] = strlen(def_videorate);

	std::cout << "vido rate:" << text[6] << std::endl;
	std::cout << "vido length:" << strlen(def_videorate) << std::endl;


}


int main(void)
{
	initconfig();
	/*
	std::cout << "def_name:" << def_name << std::endl;
	std::cout << "def_passwd:" << def_pwd << std::endl;
	std::cout << "def_serverip:" << def_serverip << std::endl;
	std::cout << "text_len[3]:" << text_len[3] << std::endl;
	std::cout << "text[0]:" << text[0] << std::endl;
	std::cout << "text_len[0]:" << text_len[0] << std::endl;

	system("pause");
	return 0;
	*/

	InitializeCriticalSection(&gLockMat);

	/* Platform */
	static GLFWwindow *win;
	int width = 0, height = 0;
	struct nk_colorf bg;
	/* GLFW */
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		fprintf(stdout, "[GFLW] failed to init!\n");
		exit(1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Virtual Live Broadcasting Application", NULL, NULL);

	glfwMakeContextCurrent(win);
	glfwGetWindowSize(win, &width, &height);


	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glewExperimental = 1;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to setup GLEW\n");
		exit(1);
	}


	ctx = nk_glfw3_init(win, NK_GLFW3_INSTALL_CALLBACKS);
	/* Load Fonts: if none of these are loaded a default font will be used  */
	/* Load Cursor: if you uncomment cursor loading please hide the cursor */
	{
		struct nk_font_atlas *atlas;
		nk_glfw3_font_stash_begin(&atlas);
		struct nk_font *cousine = nk_font_atlas_add_from_file(atlas, "./extra_font/Cousine-Regular.ttf", 15, 0);
		nk_glfw3_font_stash_end();
		nk_style_set_font(ctx, &cousine->handle);
	}

	bool LONGIN = false;
	bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
	while (!glfwWindowShouldClose(win))
	{
		/* Input */
		glfwPollEvents();
		nk_glfw3_new_frame();

		if (!LONGIN) {
			/* GUI */
			if (nk_begin(ctx, "user login", nk_rect(485, 275, 230, 150), NK_WINDOW_TITLE))
			{
				nk_layout_row_static(ctx, 20, 80, 2);
				nk_label(ctx, "user name", NK_TEXT_LEFT);


				nk_edit_string(ctx, NK_EDIT_SIMPLE, text[0], &text_len[0], 64, nk_filter_default);



				int i = 0;
				int old_len = text_len[1];


				nk_label(ctx, "password", NK_TEXT_LEFT);
				{


					for (i = 0; i < text_len[1]; ++i) buffer[i] = '*';
					nk_edit_string(ctx, NK_EDIT_FIELD, buffer, &text_len[1], 64, nk_filter_default);
					if (old_len < text_len[1])
						memcpy(&text[1][old_len], &buffer[old_len], (nk_size)(text_len[1] - old_len));
				}

				static int property = 20;
				nk_layout_row_static(ctx, 30, 200, 1);
				if (nk_button_label(ctx, "Login")) {
					LONGIN = true;

				}

			}
			nk_end(ctx);
		}
		else {
			if (!nk_window_is_closed(ctx, "user login")) {
				nk_window_close(ctx, "user login");
			}
			setting_video(ctx);
			//�������
			if (SetConfig && start == 0) {
				if (startlisten() == 1) {
					std::cout << "aaaa" << std::endl;
				}
			}
			//����
		}



		/* Draw */
		glfwGetWindowSize(win, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(bg.r, bg.g, bg.b, bg.a);
		nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
		glDeleteTextures(1, &tex);
		glfwSwapBuffers(win);
	}
	if (start == 1) {

		//�رղɼ�ָ��
		GXSendCommand(hDevice, GX_COMMAND_ACQUISITION_STOP);
		GXUnregisterCaptureCallback(hDevice);
		Valley_Release(m_hRoom);
		Valley_CleanSDK();


		if (!pBufferRGB)
		{
			delete[] pBufferRGB;
			pBufferRGB = nullptr;
		}

	}


	nk_glfw3_shutdown();
	glfwTerminate();
	DeleteCriticalSection(&gLockMat);
	return 0;
}

int startlisten() {
	start = 1;

	auto timeNow2 = returntime();

	GX_STATUS status;
	GX_OPEN_PARAM stOpenParam;
	uint32_t nDeviceNum = 0;

	// ��ʼ�����������
	char buff[1024];
	_getcwd(buff, 1024);
	std::string strProject(buff);
	std::string basicPath = strProject + "\\workfolder";

	Valley_InitSDK(basicPath.c_str(), "<?xml version=\"1.0\" encoding=\"utf-8\"?><root><localversion>1</localversion></root>");
	m_hRoom = Valley_CreateChannel(false);

	Valley_EnableInterface(m_hRoom, IID_RTCMSGR | IID_USERS | IID_AUDIO | IID_AUDIOSYSTEM | IID_AUDIOCTRL);

	const char* ip = text[3];
	//@20190515 �ر�����KEY��ʹ��
	/*
	if ((ip != "192.0.0.83") && (ip != "192.0.0.111")) {
	Valley_SetAuthKey("5a004a00bb039df5jpaDY8");
	}
	*/
	// ����Key


	// ���ù����������ļ�
	char xmlcfg[512];
	sprintf(xmlcfg, "<?xml version=\"1.0\" encoding=\"utf-8\"?><root><mcu><channel>s-%s:8002</channel></mcu><audio><channel_left>s-%s:9005</channel_left></audio></root>", ip, ip);
	Valley_SetChannelAttr(m_hRoom, RESERVE_CHANNEL_ATTR_CONFIG, xmlcfg);

	// ������Ƶ
	Valley_EnableLocalAudio(m_hRoom, true);

	// ��¼����// ������û�ID 110, �����ٱ������û�ʹ��
	int ec = Valley_Login(m_hRoom, "10", "110");
	// �ж��Ƿ��¼�ɹ�
	if (ERR_SUCCEED != ec)
	{
		std::cout << "Login Room Fail" << std::endl;
		return -1;
	}

	status = GXInitLib();
	if (status != GX_STATUS_SUCCESS)
	{
		//return EXIT_FAILURE;
		std::cout << "video init is error!~" << std::endl;
		return -1;

	}

	// ö���豸�б�
	while ((status != GX_STATUS_SUCCESS) || (nDeviceNum <= 0))
	{
		std::cout << "search cam drice" << std::endl;
		status = GXUpdateDeviceList(&nDeviceNum, 1000);
		//return -1;
	}

	//��ȡ�����豸�Ļ�����Ϣ
	GX_DEVICE_BASE_INFO *pBaseinfo = new GX_DEVICE_BASE_INFO[nDeviceNum];
	size_t nSize = nDeviceNum * sizeof(GX_DEVICE_BASE_INFO);
	GXGetAllDeviceBaseInfo(pBaseinfo, &nSize);

	// ��ӡ��ʼ
	for (uint32_t i = 0; i < nDeviceNum; ++i)
	{
		deviceInfoMap.insert(std::pair<uint32_t, char*>(i, pBaseinfo->szSN));
		std::cout << " DeviceNum:" << i << " | SN = " << pBaseinfo->szSN << ",AccessStatus = " << pBaseinfo->accessStatus << std::endl;
		pBaseinfo++;
	}
	//std::cout << deviceInfoMap.at(0) << std::endl;
	// ����������Ŵ��豸
	//�򿪵�һ�����
	stOpenParam.accessMode = GX_ACCESS_EXCLUSIVE;
	stOpenParam.openMode = GX_OPEN_SN;
	stOpenParam.pszContent = deviceInfoMap.at(0);

	// ���豸
	status = GXOpenDevice(&stOpenParam, &hDevice);
	if (status == GX_STATUS_SUCCESS)
	{
		std::cout << "open sucess" << std::endl;
		// ���òɼ�ģʽΪ�����ɼ�
		GXSetEnum(hDevice, GX_ENUM_ACQUISITION_MODE, GX_ACQ_MODE_CONTINUOUS);
		GXSetInt(hDevice, GX_INT_ACQUISITION_SPEED_LEVEL, 1);
		GXSetInt(hDevice, GX_INT_GEV_PACKETSIZE, 1500);

		// �ر��Զ���ƽ��
		GXSetEnum(hDevice, GX_ENUM_AWB_LAMP_HOUSE, GX_AWB_LAMP_HOUSE_ADAPTIVE);
		GXSetEnum(hDevice, GX_ENUM_BALANCE_WHITE_AUTO, GX_BALANCE_WHITE_AUTO_ONCE);

		GXSetEnum(hDevice, GX_ENUM_ACQUISITION_FRAME_RATE_MODE, GX_ACQUISITION_FRAME_RATE_MODE_ON);
		GXSetFloat(hDevice, GX_FLOAT_ACQUISITION_FRAME_RATE, 20.0);

		//std::cout << "Open Camera Success" << std::endl;

		// ���ͼƬ��С���ߴ�
		GXGetInt(hDevice, GX_INT_PAYLOAD_SIZE, &nPayLoadSize);
		GXGetInt(hDevice, GX_INT_WIDTH, &nImageWidth);
		GXGetInt(hDevice, GX_INT_HEIGHT, &nImageHeight);

		// ����Mat
		mat.create((int)nImageHeight, (int)nImageWidth, CV_8UC3);

		// �ж�����Ƿ���Bayer��ʽ
		bool bColorFilter;
		GXIsImplemented(hDevice, GX_ENUM_PIXEL_COLOR_FILTER, &bColorFilter);
		if (bColorFilter)
		{
			GXGetEnum(hDevice, GX_ENUM_PIXEL_COLOR_FILTER, &nPixelColorFormat);
		}

		// ��ʼ����ͼ��洢�����ݻ���
		pBufferRGB = new BYTE[(size_t)(nImageWidth*nImageHeight * 3)];
		if (!pBufferRGB)
		{
			std::cout << "Buffer RGB Malloc Fail" << std::endl;
			return EXIT_FAILURE;
		}

		pBufferRaw = new BYTE[(size_t)(nPayLoadSize)];
		if (!pBufferRaw)
		{
			std::cout << "Buffer RAW Malloc Fail" << std::endl;
			// �Ƿ�RGB�Ŀռ�,��ΪRAW����ʧ�ܵ���RGB�϶������ɹ�
			delete[] pBufferRGB;
			pBufferRGB = nullptr;

			return EXIT_FAILURE;
		}

		// ������ַ
		// ��ʼ������
		const char * streamUrl = "aaa.264";
		webStreamer = new BMPStreamer_web(streamUrl, nImageWidth, nImageHeight, fps);
		if (!webStreamer->web_stat)
		{
			std::cout << "Web Streamer Init Error" << std::endl;
			return EXIT_FAILURE;
		}


		//ע��ͼ����ص�����
		GXRegisterCaptureCallback(hDevice, NULL, OnFrameCallbackFun);
		//���Ϳ�������
		GXSendCommand(hDevice, GX_COMMAND_ACQUISITION_START);

		return 1;
	}
	else
	{
		std::cout << "Open Device Fail" << std::endl;
		return -1;
	}




}