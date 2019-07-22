// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
#define _CRT_SECURE_NO_WARNINGS
#ifndef PCH_H
#define PCH_H

// TODO: 添加要在此处预编译的标头

#endif //PCH_H
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>
//#include <unistd.h>
extern "C"
{
#include "libavutil/opt.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/time.h"
#include "libavutil/mathematics.h"
};



class BMPStreamer_web
{
public:
	AVFormatContext* pFormatCtx;
	AVOutputFormat* fmt;
	AVStream* video_st;
	AVCodecContext* pCodecCtx;
	AVCodec* pCodec;
	AVPacket pkt;
	AVPacket pkt_tmp;
	uint8_t* picture_buf, *buffer;
	AVFrame* pFrame, *rgbFrame;
	uint8_t* frame_buf;
	SwsContext * scxt;
	//std::mutex mt;
	int picture_size;
	int y_size;
	uint64_t framecnt;
	int rgb_w, rgb_h;
	int rgb_pixelsize;
	AVPixelFormat fla;
public:
	int fpscount;
	int web_stat;
	uint8_t* rgb_buf;

	double fpstime;
	int fps;
	int used;

	int threadlive;
	//AVBitStreamFilterContext* aacbsfc;
	long long first_time = 0;
	//hq12.26
	//__int64 first_time = 0;
	int64_t	current_time = 0;
	int64_t a_first_time = 0;
	int64_t	a_current_time = 0;

	//FILE *fp1;

	int got_picture = 0;

	BMPStreamer_web(const char *url, int in_w = 1920, int in_h = 1080, int ifps = 30)
	{
		//fp1 = fopen("test2.264", "wb");
		used = 0;
		fps = ifps;
		fpscount = 0;
		fpstime = 1.0 / 25;
		threadlive = 1;
		framecnt = 0;
		rgb_buf = NULL;
		web_stat = 1;

		av_register_all();
		//Network
		avformat_network_init();
		//debug
		//const char* out_file = "src01.ts";
		//Output
		avformat_alloc_output_context2(&pFormatCtx, NULL, NULL, url);
		//avformat_alloc_output_context2(&pFormatCtx, NULL, "rtsp", url);//mpegts
		fmt = pFormatCtx->oformat;
		if (avio_open(&pFormatCtx->pb, url, AVIO_FLAG_READ_WRITE) < 0) {
			printf("Failed to open output file! \n");
			web_stat = 0;
			//exit(-1);
		}

		pCodec = avcodec_find_encoder(AV_CODEC_ID_H264);
		if (!pCodec) {
			printf("Can not find encoder! \n");
			web_stat = 0;
			//exit(-1);
		}

		video_st = avformat_new_stream(pFormatCtx, pCodec);
		if (video_st == NULL) {
			printf("Failed to open stream! \n");
			web_stat = 0;
			//exit(-1);
		}
		printf("[Info] Stream Opened.\n");
		AVRational time_base = { 1, 90000 };
		video_st->time_base = time_base;

		//set out stream flags and tags
		video_st->codec->codec_tag = 0;
		if (pFormatCtx->oformat->flags & AVFMT_GLOBALHEADER)
			video_st->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
		video_st->time_base.num = 1;
		video_st->time_base.den = ifps;

		//Param that must set
		video_st->r_frame_rate.den = ifps;
		video_st->r_frame_rate.num = 1;
		//Param that must set
		pCodecCtx = video_st->codec;
		pCodecCtx->codec_id = AV_CODEC_ID_H264;
		//pCodecCtx->codec_id = pFormatCtx->oformat->video_codec;
		pCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
		pCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
		pCodecCtx->width = in_w;
		pCodecCtx->height = in_h;
		pCodecCtx->time_base.num = 1;
		pCodecCtx->time_base.den = ifps;
		pCodecCtx->bit_rate =8000000;  //byte as  
		
		

		pCodecCtx->gop_size = 1; //90
		
		pCodecCtx->qmin = 22; //30
		pCodecCtx->qmax = 50;//50
							 //pCodecCtx->global_quality = 1;

		pCodecCtx->max_b_frames = 0;
		// Set Option
		AVDictionary *param = 0;
		//H.264
		//av_dict_set(&param, "threads", "8", 0);
		if (pCodecCtx->codec_id == AV_CODEC_ID_H264) {
			av_dict_set(&param, "preset", "ultrafast", 0);
			av_dict_set(&param, "tune", "zerolatency", 0);
			av_dict_set(&param, "i_qfactor", "1.0", 0);
			av_dict_set(&param, "profile", "main", 0);
			//av_dict_set(&param, "qp", "0", 0);

		}

		std::cout << "bit rate:" << pCodecCtx->bit_rate << std::endl;

		//Show some Information
		av_dump_format(pFormatCtx, 0, url, 1);


		if (avcodec_open2(pCodecCtx, pCodec, &param) < 0) {
			printf("Failed to open encoder! \n");
			//exit(-1);
			web_stat = 0;
		}

		printf("[Info] Codec Loaded.\n");


		pFrame = av_frame_alloc();
		rgbFrame = av_frame_alloc();
		picture_size = avpicture_get_size(pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height);
		picture_buf = (uint8_t *)av_malloc(picture_size);

		avpicture_fill((AVPicture *)pFrame, picture_buf, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height);


		printf("[Info] Create encode buffer.\n");
		pFrame->width = pCodecCtx->width;
		pFrame->height = pCodecCtx->height;
		pFrame->format = pCodecCtx->pix_fmt;

		int pixelsize = 3;//AV_PIX_FMT_BGR24

		rgb_buf = (uint8_t *)av_malloc(in_w*in_h*pixelsize);

		memset(rgb_buf, 255, in_w*in_h*pixelsize);//黑色填充

		avpicture_fill((AVPicture*)rgbFrame, rgb_buf, AV_PIX_FMT_BGR24, in_w, in_h);
		scxt = sws_getContext(in_w, in_h, AV_PIX_FMT_BGR24, video_st->codec->width, video_st->codec->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);


		avformat_write_header(pFormatCtx, NULL);
		printf("[Info] Write Stream Header.\n");

		av_new_packet(&pkt, picture_size);

		y_size = pCodecCtx->width * pCodecCtx->height;



	}


	void encode()
	{

		avpicture_fill((AVPicture*)rgbFrame, rgb_buf, AV_PIX_FMT_BGR24, video_st->codec->width, video_st->codec->height);
		sws_scale(scxt, rgbFrame->data, rgbFrame->linesize, 0, video_st->codec->height, pFrame->data, pFrame->linesize);
		//avio_alloc_context();
		
		pFrame->pts = framecnt;
		//Encode
		int ret = avcodec_encode_video2(pCodecCtx, &pkt, pFrame, &got_picture);
		if (ret < 0) {
			printf("Failed to encode! \n");
			web_stat = 0;
			//exit(-1);
		}
		if (got_picture == 1) {
			pkt.pts = framecnt * 1000 / fps;
			pkt.dts = pkt.pts;
			pkt.duration = 1000 / fps;
			pkt.stream_index = video_st->index;
			//pkt_tmp = pkt;
			//fwrite(pkt.data, pkt.size, 1, fp1);
			//ret = av_interleaved_write_frame(pFormatCtx, &pkt);
			//if (ret < 0) {
			//	printf("Error muxing packet\n");
			//	web_stat = 0;
			//	//break;
			//}
			framecnt++;
			web_stat = 1;
		}
	}

	void release_pkt()
	{
		if (got_picture == 1) {
			if (web_stat == 1)
			{
				av_free_packet(&pkt);
			}
		}
	}

	~BMPStreamer_web()
	{
		threadlive = 0;

		//	sleep(2);


		if (rgb_buf) delete[] rgb_buf;
		if (buffer) delete[] buffer;

		int ret = flush_encoder(pFormatCtx, 0);
		if (ret < 0) {
			printf("Flushing encoder failed\n");
			web_stat = 0;
			//exit(-1);
		}


		//Clean
		if (video_st) {
			avcodec_close(video_st->codec);
			av_free(pFrame);
			av_free(picture_buf);
		}
		avio_close(pFormatCtx->pb);



		avformat_free_context(pFormatCtx);



	}



	int flush_encoder(AVFormatContext *fmt_ctx, unsigned int stream_index) {
		int ret;
		int got_frame;
		AVPacket enc_pkt;
		if (!(fmt_ctx->streams[stream_index]->codec->codec->capabilities &
			CODEC_CAP_DELAY))
			return 0;
		while (1) {
			enc_pkt.data = NULL;
			enc_pkt.size = 0;
			av_init_packet(&enc_pkt);
			ret = avcodec_encode_video2(fmt_ctx->streams[stream_index]->codec, &enc_pkt,
				NULL, &got_frame);
			av_frame_free(NULL);
			if (ret < 0)
				break;
			if (!got_frame) {
				ret = 0;
				break;
			}
			printf("Flush Encoder: Succeed to encode 1 frame!\tsize:%5d\n", enc_pkt.size);
			/* mux encoded frame */
			ret = av_write_frame(fmt_ctx, &enc_pkt);
			if (ret < 0)
				break;
		}
		return ret;
	}



};
