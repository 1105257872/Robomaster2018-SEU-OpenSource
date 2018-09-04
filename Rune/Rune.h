/**************************************************************

MIT License

Copyright (c) 2018 SEU-SuperNova-CVRA

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Authors:	Shi Shu, <213162637@seu.edu.cn>
            BinYan Hu
            Su ChenHao
            Cui RenJie
            Sun BoWen
**************************************************************/
#pragma once

#include"../General/singleton.hpp"
#include"../General/General.h"
#include"../General/opencv_extended.h"
#include<opencv2/opencv.hpp>
#include<array>

//#define SHOW_PRETREAT						/*to show the process of pretreat*/
//#define SHOW_FIND_LED						/*to show the process of finding led*/
//#define DEBUG_FULL                        /*to show the process of detecting rune*/
//#define DEBUG_NUM                         /*to show the result of caculating numbers*/


#define DEBUG_GET_EVERYTHING                /*to get mumbers of classes*/
//#define CASUAL_SET_NUMBER                 /*to set led numbers and rune numbers while debugging*/

namespace rm
{
/*
 * this class contains all possibly modified parameters which may be used at the playing field
*/
	class RuneParam
	{
	public:
		RuneParam(const int _hsv_h_min = 0,
			const int _hsv_h_max = 34,
			const int _hsv_s_min = 43,
			const int _hsv_s_max = 255,
			const int _hsv_v_min = 150,
			const int _hsv_v_max = 255,
			const int _contour_min_area = 130,
			const float _contour_boundingrect_min_aspect_ratio = 0.25,
			const int _contour_boundingrect_max_aspect_ratio = 4,
			const int _contour_boundingrect_min_area = 200,
			const int _contour_boundingrect_max_area = 3000,
			const float _y_direction_dx_max_width_rate = 0.5,
			const float _y_direction_dy_max_height_rate = 2.5,
			const float _x_direction_dx_min_height_rate = 1.5,
			const float _x_direction_dx_max_height_rate = 3.5,
			const float _x_direction_dy_max_height_rate = 1.0,
			const float _centers_max_sin_theta = 0.30) :
			hsv_h_min(_hsv_h_min),
			hsv_h_max(_hsv_h_max),
			hsv_s_min(_hsv_s_min),
			hsv_s_max(_hsv_s_max),
			hsv_v_min(_hsv_v_min),
			hsv_v_max(_hsv_v_max),
			contour_min_area(_contour_min_area),
			contour_boundingrect_min_aspect_ratio(_contour_boundingrect_min_aspect_ratio),
			contour_boundingrect_max_aspect_ratio(_contour_boundingrect_max_aspect_ratio),
			contour_boundingrect_min_area(_contour_boundingrect_min_area),
			contour_boundingrect_max_area(_contour_boundingrect_max_area),
			y_direction_dx_max_width_rate(_y_direction_dx_max_width_rate),
			y_direction_dy_max_height_rate(_y_direction_dy_max_height_rate),
			x_direction_dx_min_height_rate(_x_direction_dx_min_height_rate),
			x_direction_dx_max_height_rate(_x_direction_dx_max_height_rate),
			x_direction_dy_max_height_rate(_x_direction_dy_max_height_rate),
			centers_max_sin_theta(_centers_max_sin_theta)
		{

		}

		const RuneParam operator=(const RuneParam & runeParam)
		{
			this->hsv_h_min = runeParam.hsv_h_min;
			this->hsv_h_max = runeParam.hsv_h_max;
			this->hsv_s_min = runeParam.hsv_s_min;
			this->hsv_s_max = runeParam.hsv_s_max;
			this->hsv_v_min = runeParam.hsv_v_min;
			this->hsv_v_max = runeParam.hsv_v_max;

			this->contour_min_area = runeParam.contour_min_area;
			this->contour_boundingrect_min_aspect_ratio = runeParam.contour_boundingrect_min_aspect_ratio;
			this->contour_boundingrect_max_aspect_ratio = runeParam.contour_boundingrect_max_aspect_ratio;
			this->contour_boundingrect_min_area = runeParam.contour_boundingrect_min_area;
			this->contour_boundingrect_max_area = runeParam.contour_boundingrect_max_area;

			this->y_direction_dx_max_width_rate = runeParam.y_direction_dx_max_width_rate;
			this->y_direction_dy_max_height_rate = runeParam.y_direction_dy_max_height_rate;
			this->x_direction_dx_min_height_rate = runeParam.x_direction_dx_min_height_rate;
			this->x_direction_dx_max_height_rate = runeParam.x_direction_dx_max_height_rate;
			this->x_direction_dy_max_height_rate = runeParam.x_direction_dy_max_height_rate;
			this->centers_max_sin_theta = runeParam.centers_max_sin_theta;
			return *this;
		}
	

		int hsv_h_min = 0;							/*����ʱ��hͨ��ѡ��������Сֵ*/
		int hsv_h_max = 34;							/*����ʱ��hͨ��ѡ���������ֵ*/
		int hsv_s_min = 43;							/*����ʱ��sͨ��ѡ��������Сֵ*/
		int hsv_s_max = 255;						/*����ʱ��sͨ��ѡ���������ֵ*/
		int hsv_v_min = 150;						/*����ʱ��vͨ��ѡ��������Сֵ*/
		int hsv_v_max = 255;						/*����ʱ��vͨ��ѡ���������ֵ*/

		int contour_min_area = 130;							/*�����ڲ�����С���*/
		int contour_boundingrect_min_aspect_ratio = 0.25;	/*����������ε���С�����*/
		int contour_boundingrect_max_aspect_ratio = 4;		/*����������ε���󳤿��*/
		int contour_boundingrect_min_area = 200;			/*����������ε���С���*/
		int contour_boundingrect_max_area = 3000;			/*����������ε�������*/

		float y_direction_dx_max_width_rate = 0.5;			/*y���������ٽ�����ʱ������������Ƚ�dx����׼���θ߶ȵ������*/
		float y_direction_dy_max_height_rate = 2.5;			/*y���������ٽ�����ʱ������������Ƚ�dy����׼���ο�ȵ������*/
		float x_direction_dx_min_height_rate = 1.5;			/*x���������ٽ�����ʱ������������Ƚ�dx����׼���θ߶ȵ���С����*/
		float x_direction_dx_max_height_rate = 3.5;			/*x���������ٽ�����ʱ������������Ƚ�dx����׼���θ߶ȵ������*/
		float x_direction_dy_max_height_rate = 1.0;			/*x���������ٽ�����ʱ������������Ƚ�dy����׼���θ߶ȵ������*/
		float centers_max_sin_theta = 0.30;					/*������������������ĵ�֮��нǵ�����ֵ*/

	};
	
    class RuneDetector
	{
	public:
        //RuneDetector() {};
        //~RuneDetector() {};
		enum RuneFlag
		{
			RUNE_NO = 0,//δʶ���
			RUNE_PART = 1,//���������������δȫ������
			RUNE_FULL = 2,//ȫ�����ɹ�
			SHOOT_NO = 3,//���ڻ����ܴ�
            SHOOT_WAIT = 4,//�Ѿ������˴��������㣬����δ����,
			SHOOT_YES = 5,//�Ѿ�����
		};

		/*
		*	@brief ��ʼ�����������
		*/
        void init();

        /*
        *	@brief ����ͼƬ
        */
        void setMode(int runeMode, const RuneParam& runeParam);

		/*
		*	@brief ����ͼƬ
		*/
		cv::Mat loadImg(cv::Mat mat);

		/*
		*	@brief ����ʶ��
		*/
        int caculate();

		/*
		*	@brief ѡ��Ҫ���������ϵ�����
		*/
		cv::Point2f chooseTarget();

        /*
        *	@brief reset parameters
        */
        void resetPara();

		bool isShoot(bool shootSituation)
		{
			isFly_ = shootSituation;
			if (isFly_ == true)
			{
				shootFlag_ = SHOOT_YES;
				return true;
			}
			return false;
		}

		/*
		*	@brief ����flag
		*/
        int getFlag() const;

#ifdef DEBUG_GET_EVERYTHING
		/*
		*	@brief ��ȡ�����ROI����
		*/
		const cv::Rect getRuneRoi() const;

		/*
		*	@brief ��ȡ�Ź�������ĵ�����
		*/
		const std::array<cv::Point2f, 9> getCenters() const;

		/*
		*	@brief ��ȡ�Ź����9������
		*/
		const std::array<int, 9> getRuneNumbers() const;
		/*
		*	@brief ��ȡLED��5������
		*/
		const std::vector<int> getLedNumbers() const;



#endif // DEBUG_GET_EVERYTHING

	private:
        /*
        *	this blob contains the contours' characters found after findContours()
        */
		struct Blob
		{
			Blob() = default;
			Blob(const cv::Point2f& pcenter, const float pwidth,
				 const float pheight, const float parea)
			{
				center = pcenter;
				width = pwidth;
				height = pheight;
				area = parea;

			}
			cv::Point2f center;						/*������������ε�����*/
			float width;							/*������������εĿ�*/
			float height;							/*������������εĸ�*/
			float area;								/*�����������ȥ�����ڲ�����������������õ������*/
			cv::Point coor = {0, 0};				/*��Ӧͼ�׵��λ��*/
		};

        int runeMode_ = 0;								/*�Ǵ������С��*/
		RuneParam params_;									/*�������*/

		//TODO: double flags
		int runeFlag_;											/*�ҵ������Ź�������*/
		int shootFlag_;											/*�Ƿ��ܴ�������*/

		cv::Mat srcImg_;									/*ԭͼ*/
		cv::Mat workImg_;									/*��������ʱʹ�õ�ͼ*/
		cv::Mat perspMat_;
		cv::Mat grayImg_;
		cv::Mat debugImg_;
		const std::string debugImgName = "debug info";

		std::vector<std::vector<cv::Point>> contours_;		/*findContours���ҵ�������*/
		std::vector<cv::Vec4i> hierachy_;					/*findContours���ҵ���������Ϣ*/

		std::vector<Blob> blobs_;							/*����ɸѡ�󱣴�������������Ҫ��Ϣ*/
		std::vector<cv::Rect2f> filteredRects_;					/*����ɸѡ��������������*/
		//std::vector<cv::Rect2f> final_Rects_;				/*�����ڶ���ɸѡ��ʣ�µ������������*/
		std::vector<Blob> finalBlobs_;						/*�����ڶ���ɸѡ��ʣ�µ�������Ϣ*/
		
		std::array<cv::Point2f, 9> runeCenters_;			/*�����9�����ĵ�*/
		std::array<int, 9> runeNumbers_;					/*�����9������*/
		std::array<int, 9> oldruneNumbers_;					/*�����9������*/
		std::array<std::pair<cv::Point2f, int>, 9> numbersNcenter_;/*�����9�����ֺ����ĵ�*/
		cv::Rect rune_roi_;									/*�����ROI����*/

		cv::Rect ledRoi_;									/* �������������(���srcImg) */		
		cv::Mat ledImg_;									/* �����ͼƬ ԭͼ��ֱ�Ӳü������Ĳ�ɫͼ*/	
		
		cv::Mat ledProcessingImg_;							/*����ܲ������ڽ���һϵ�в�����һ������*/
		std::vector<cv::Rect> ledRects_;					/* LED�ָ��� */
		std::vector<int> runeLedNumbers_;					/*led��5������*/
		std::vector<int> oldruneLedNumbers_;				/*led�ϴε�5������*/

		std::list<int> history_;							/*�洢��ȥ5��LED�Ľ��*/
		int led_idx_ = 0;									/*��¼���ڴ��������ܵĵڼ�������(��Χ0~4)*/
		std::array<int, 10> vote;								/*��¼ͶƱ���*/
		cv::Point2f targetCoor_;									/*��¼����Ŀ���ھŹ���ͼ�׵�����*/
		bool isFly_ = false;									/*��¼�ӵ��Ƿ��䣬������Ϊtrue*/

		int debug_count_ = 1;
															
		/*
		*	@brief �ж��Ƿ��Ǵ��
		*/
		int isGreatRune(int runeMode);


		/*
		*	@brief ��HSVͼƬ��ѡȡ�Լ���Ҫ����ɫ
		*	@param1 hͨ������Сֵ
		*	@param2 hͨ�������ֵ
		*	@param3 sͨ������Сֵ
		*	@param4 sͨ�������ֵ
		*	@param5 vͨ������Сֵ
		*	@param6 vͨ�������ֵ
		*	@information
		*				yellow channle of HSV
		*			H��[26,34] S��[43,255] V��[46,255]
		*/
		void chooseColor(int hsv_h_min, int hsv_h_max,
			int hsv_s_min, int hsv_s_max,
			int hsv_v_min, int hsv_v_max);

		/*
		*	@brief ��������������εĴ�С������Լ���ֵ���������ڲ��ڵ�ռ�ȳ����ų������־���
		*/
		void preScreen();

		/*
		*	@brief �����������������˼���ʣ�µ�Blob���й��ˣ�
		*		�����ʣ�µ�Blob����ͼ�ף�ͨ����ͼ�����ĵ�ɸѡ��
		*		ѡ���Ź�������ģ��Ӷ�ȷ���Ź����λ��
		*/
		void findRune();

		/*
		*	@brief ʶ������ܵ�����
		*/
        const std::vector<int> findLedNumbers();

		/*
		*	@brief 	ȫ������Ӧ��ֵ
		*			1.����Ҷ�ֱ��ͼ
		*			2.�ԻҶ�ֱ��ͼ����6�ζ���ʽ���
		*			3.ͨ����ֵķ��ű仯�õ��������ķ�
		*			
		*	���Կ��ǶԲ�ͬ������ò�ͬ�����Ķ���ʽ��ϣ�6�αȽ��ʺ�ֱ��ͼ������������������
		*/
		int findLEDThreshold(const cv::Mat & gray);

		/*
		*	@brief ��������ʶ������Ϊ��������ͼƬ���ڵװ���
		*/
		int trans2RealLedNum(const cv::Mat& dframe_count);

		/*
		*	@brief �и�ledImg_���õ���������������
		*/
        void getLedImg();

		
		/*
		*	@brief Ѱ�����
		*/
		void  detect();

		/*
		*	@brief �ָ��ʶ������
		*/
		void recognize();

		/*��Ҫ������ּ�¼��history_�У�1-9��¼�ɹ���-1��¼ʧ��*/
		bool setRecord(int record);

		/*ѡ��Ҫ���������*/
		int chooseNumber();


	};

}
