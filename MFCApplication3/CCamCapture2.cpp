#include "stdafx.h"
#include "CCamCapture2.h"


cv::Mat CCamCapture2::m_pImage;

CCamCapture2::CCamCapture2()
{
	
}

CCamCapture2::~CCamCapture2()
{
}

BOOL CCamCapture2::CreateCapture()
{
	if (m_bCamInited)
	{
		return TRUE;
	}
	else
	{
		if (m_pThread)
		{
			ExitProcess(3);
			m_heventThreadDone = AfxBeginThread(threadGrabImage, (LPVOID)this);
		}
	}
}

void CCamCapture2::DestoryCapture()
{
	if (m_bCamInited)
	{
		StopCapture();
		WaitForSingleObject(m_heventThreadDone,INFINITE);
	}
}

void CCamCapture2::StartCapture()
{
	Cam = START;
}

void CCamCapture2::PauseCapture()
{
	Cam = PAUSE;
}

void CCamCapture2::StopCapture()
{
	Cam = STOP;
}

void CCamCapture2::doGrabLoop()
{
	cv::Mat frame;
	while (m_bCamInited)
	{
		if (Cam == START)
		{
			
			m_cap >> frame;
			if (frame.empty())
			{
				break;
			}
			frame.copyTo(m_pImage);
			
		}

		else if (Cam == PAUSE)
		{
			if (m_pImage.empty())
			{

			}
		}
		else
		{
			m_bCamInited = false;
		}
	}
}

void CCamCapture2::onGrabLoop_cvInit()
{
	m_cap.open(0);

	if (m_cap.isOpened())
	{
		m_bCamInited = TRUE;
		PauseCapture();
	}
	else
	{
		m_bCamInited = FALSE;
	}
}

void CCamCapture2::onGrabLoop_cvClose()
{
	if (m_cap.isOpened())
	{
		m_cap.release();
	}
}
void CCamCapture2::onMouseCB2(int event, int x, int y, int flags, void* param)
{
	//CvPoint p1, p2;
	//if (m_bTargetObj == false && event == CV_EVENT_LBUTTONDOWN)
	//{
	//	m_Origin.x = x;
	//	m_Origin.y = y;
	//	m_bTargetObj = true;

	//}
	//else if (m_bTargetObj == true && event == CV_EVENT_MOUSEMOVE)
	//{

	//	p1 = cvPoint(m_Origin.x, m_Origin.y);
	//	p2 = cvPoint(x, y);
	//	rectangle(m_pImage, cv::Point(p1), cv::Point(p2), cv::Scalar(0, 255, 0), 2);
	//	cv::imshow("ShowImage", m_pImage);

	//}
	//else if (m_bTargetObj == true && event == CV_EVENT_LBUTTONUP)
	//{
	//	m_TargetRect = cv::Rect(cv::Point(m_Origin.x, m_Origin.y), cv::Point(x, y));
	//	if (m_TargetRect.width && m_TargetRect.height)
	//	{
	//		m_ROI = frame(m_TargetRect);
	//		cv::imshow("roi", m_ROI);
	//		//waitKey(0);  
	//	}
	//	m_bTargetObj = false;
	//}
}

UINT CCamCapture2::threadGrabImage(LPVOID pParam)
{
	CCamCapture2* pCapture = ((CCamCapture2*)pParam);

	pCapture->doGrabLoop();

	return 0;
}

void CCamCapture2::onGrabLoop_DrawROI(cv::Mat& frame)
{
	if (m_bTargetObj)
	{

	}
	else
	{

	}
}