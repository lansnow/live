/*
设置直播流相关的信息
//设置配置成功后，后面再显示服务器相关的操作

*/
static struct nk_image mat_load(cv::Mat &src);
static void die(const char *fmt, ...);

//这里是全局配置
//static char config[4][64];
//static int text_len[4];
extern char text[6][64];
extern int text_len[6];

extern cv::Mat mat;
extern cv::Mat realMat;
extern cv::Mat all_dsc;

extern int min_green;
extern int max_green;
extern int cutwidth;
extern int bgindexNum;
extern bool showVideo;
extern cv::VideoCapture cap;
GLuint tex;


static void setting_video(struct nk_context *ctx)
{
	
	if (nk_begin(ctx, "video setting", nk_rect(0, 0, 260, 1200), NK_WINDOW_TITLE))
	{
		nk_layout_row_static(ctx, 20, 100, 2);
		nk_label(ctx, "Server IP:", NK_TEXT_LEFT);
		
		nk_edit_string(ctx, NK_EDIT_SIMPLE, text[3], &text_len[3], 250, nk_filter_default);

		
		nk_layout_row_static(ctx, 20, 100, 2);
		nk_label(ctx, "Video rate:", NK_TEXT_LEFT);
		nk_edit_string(ctx, NK_EDIT_SIMPLE, text[6], &text_len[6], 250, nk_filter_default);


		nk_layout_row_static(ctx, 30, 180, 1);
		
		

		if (nk_button_label(ctx, "Setting")) {


			//std::cout << "Server IP:" << config[0] << std::endl;
			SetConfig = true;
		}


		static nk_size m_prog = (nk_size)text[4];
		static nk_size d_prog = (nk_size)text[5];
		static nk_size videorate = (nk_size)text[6];
		static nk_size cut_width;

		//服务器设置成功后，这里需要调出扣图的配置信息
		if (SetConfig) {

			nk_label(ctx, "Min Green:", NK_TEXT_LEFT);
			nk_progress(ctx, &m_prog, 100, NK_MODIFIABLE);
			nk_label(ctx, "Max Green:", NK_TEXT_LEFT);
			nk_progress(ctx, &d_prog, 100, NK_MODIFIABLE);

			min_green = (int)m_prog;
			max_green = (int)d_prog;

			nk_label(ctx, "cut width:", NK_TEXT_LEFT);
			nk_progress(ctx, &cut_width, 400, NK_MODIFIABLE);

			cutwidth = (int)cut_width;

			nk_label(ctx, "Video rate:", NK_TEXT_LEFT);
			nk_progress(ctx, &videorate, 30, NK_MODIFIABLE);
			//defrate = (int)videorate;

			//std::cout << "m_prog:" << m_prog << std::endl;
			//std::cout << "d_prog:" << d_prog << std::endl;

			if (nk_button_label(ctx, "Chang background")) {

				bgindexNum = (bgindexNum % 6) + 1;
				std::cout << "bg index:" << (int)bgindexNum << std::endl;

			}

			if (nk_button_label(ctx, "show Video")) {

				showVideo = !showVideo;
				if (showVideo) {
					cap.open("./video/test.mp4");
					if (!cap.isOpened()) {
						showVideo = false;
					}
				}
				else {
					cap.release();
				}
				

			}



		}


	}
	nk_end(ctx);
	std::string default_pic = "./loading.jpg";
	//std::string default_pic = "D:\\111.jpg";
	if (nk_begin(ctx, "video show", nk_rect(260, 0, 900, 1200), NK_WINDOW_TITLE))
	{
		nk_layout_row_static(ctx, 482, 856, 1);

		EnterCriticalSection(&gLockMat);
		if (!realMat.empty()) {
			nk_image(ctx, mat_load(realMat));
		}
		else {
			all_dsc = cv::imread(default_pic);
			nk_image(ctx, mat_load(all_dsc));
		}
		LeaveCriticalSection(&gLockMat);

	}
	nk_end(ctx);
}

void dispVideo(struct nk_context *ctx,cv::Mat src) {

	if (nk_begin(ctx, "video show", nk_rect(260, 0, 900, 800), NK_WINDOW_TITLE))
	{
		nk_layout_row_static(ctx, 482, 856, 1);
		//cv::Mat dsc = cv::imread(src);
		nk_image(ctx, mat_load(src));

	}
	nk_end(ctx);
}

static void
die(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fputs("\n", stderr);
	exit(EXIT_FAILURE);
}


static struct nk_image
mat_load(cv::Mat &src)
{
	int x, y, n;
	
	x = src.cols;
	y = src.rows;
	unsigned char *data = src.data;
	if (!data) die("[SDL]: failed to load image");

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, x, y, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	return nk_image_id((int)tex);
}

