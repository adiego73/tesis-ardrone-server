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

	bool finish = false;

	cv::Mat frame;
	cv::Mat imageToSend;
	cv::namedWindow("camera", CV_WINDOW_AUTOSIZE);

	int sockfd;
	struct sockaddr_in serv_addr;

	// creo el socket
	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (sockfd < 0)
	{
		std::cerr << "ERROR opening socket";
		exit(EXIT_FAILURE);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(VIDEO_PORT_NUMBER);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cerr << "ERROR on binding " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	while (!finish)
	{
		frame = ardrone->getImage();

		if (!frame.empty())
		{
			cv::imshow("camera", frame);

			cv::resize(frame, imageToSend, cv::Size(180, 120), 0, 0, cv::INTER_LINEAR);

			imageToSend = (imageToSend.reshape(0, 1));
			int size = imageToSend.total() * imageToSend.elemSize();

			int send = sendto(sockfd, imageToSend.data, size, 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

			if(send < 0)
			{
				std::cerr << "ERROR sending frame via UDP socket: " << errno << std::endl;
			}
		}
		cv::waitKey(1);

		// read-only mutex
		param->m_mutex.lock_shared();
		finish = param->finish;
		param->m_mutex.unlock_shared();
	}

	std::cout << "\tTURNING OFF VIDEO SERVER" << std::endl;

	cv::destroyAllWindows();
	frame.deallocate();
	imageToSend.deallocate();
	close(sockfd);
}
