#ifndef VIDEO_HPP_
#define VIDEO_HPP_

#include <VP_Api/vp_api.h>

#include <opencv2/opencv.hpp>

C_RESULT video_process_transform(void *params, struct _vp_api_io_data_ *in,
		struct _vp_api_io_data_ *out);

C_RESULT video_process_close(void *params);

extern const vp_api_stage_funcs_t video_process_functions;

#endif /* VIDEO_HPP_ */
