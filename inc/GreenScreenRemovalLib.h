//Created by Zhengzhong Sun
//Email: zhengzhong.sun@dgene.com
//Date: 2019.3.22
//Update: 2019.4.13

#pragma once

#include<opencv2\opencv.hpp>

namespace DGene {

	class GreenScreenRemoval
	{
	public:
		struct MattingImage
		{
			cv::Mat img_matting;
			cv::Rect bbx_matting;
		};

		// Green screen removal and replace the background with black color
		// Input: 1. frame is the image with green screen
		//	      2. feather_intensity is the smooth intensity of the border, default is 6.
		//		  if the feather_intensity <= 0, it won't smooth the border.
		//        3. min_green and max_green control the range of green,
		//        min_green(0-100, default=30), max_green(0-150, default=100),
		//        min_green<=max_green
		//		  4. min_saturation(0-100) controls the minimum saturation of green.
		//		  5. min_value(0-100) controls the minimum value of green, it always means the lightness of green.
		// Return value: the MattingImage include both the image after green screen removal and the bounding box of human area.
		static MattingImage GreenScreenMatting(cv::Mat frame, int feather_intensity = 6, int min_greeen = 30, int max_green = 100, int min_saturation = 0, int min_value = 0);
	};

}