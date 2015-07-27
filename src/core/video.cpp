#include "core/video.hpp"

using namespace cv;

const vp_api_stage_funcs_t display_stage_funcs =
{
NULL,
NULL, (vp_api_stage_transform_t) video_process_transform,
		(vp_api_stage_close_t) video_process_close };

C_RESULT video_process_transform(void *params, struct _vp_api_io_data_ *in,
		struct _vp_api_io_data_ *out)
{
	uint32_t width = 640, height = 480;

	Size size(width, height);
	Mat img(size, CV_8UC3);

	img.data = (uint8_t *) in->buffers[0];

	cvtColor(img, img, CV_BGR2RGB);

	namedWindow("video", CV_WINDOW_AUTOSIZE);
	imshow("video", img);

	waitKey(1);

	img.release();

	return C_OK;
}

C_RESULT video_process_close(void *params)
{
	destroyAllWindows();

	return C_OK;
}
