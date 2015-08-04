#include "core/video_server.hpp"
#include "classes/ardrone.hpp"

void video_server(boost::shared_ptr<thread_data> param,
		boost::shared_ptr<ARDrone> ardrone)
{
	std::cout << "\tSTART VIDEO SERVER" << std::endl;

	if (param == NULL)
	{
		std::cerr << "THREAD DATA cannot be NULL" << std::endl;
		exit(EXIT_FAILURE);
	}

	bool end = false;
	cv::Mat frame;
	cv::namedWindow("camera", CV_WINDOW_AUTOSIZE);

	while (!end)
	{
		frame = ardrone->getImage();

		if (!frame.empty())
		{
			cv::imshow("camera", frame);
		}

		cv::waitKey(1);

		param->m_mutex.lock();

		if (param->action == END)
		{
			std::cout << "action == end" << std::endl;
			end = true;
		}

		param->m_mutex.unlock();
	}

	std::cout << "\tTURNING OFF VIDEO SERVER" << std::endl;

	cv::destroyAllWindows();
	frame.deallocate();
}
