#pragma once
#define USE_OPENCV 0

//#pragma comment(lib,"lib_json.lib")

#ifdef _DEBUG
#if USE_OPENCV
#pragma comment(lib,"opencv_calib3d2410d.lib")
#pragma comment(lib,"opencv_contrib2410d.lib")
#pragma comment(lib,"opencv_core2410d.lib")
#pragma comment(lib,"opencv_features2d2410d.lib")
#pragma comment(lib,"opencv_flann2410d.lib")
#pragma comment(lib,"opencv_highgui2410d.lib")
#pragma comment(lib,"opencv_imgproc2410d.lib")
#pragma comment(lib,"opencv_legacy2410d.lib")
#pragma comment(lib,"opencv_ml2410d.lib")
#pragma comment(lib,"opencv_objdetect2410d.lib")
#pragma comment(lib,"opencv_ts2410d.lib")
#pragma comment(lib,"opencv_video2410d.lib")
#pragma comment(lib,"opencv_nonfree2410d.lib")
#endif
//#pragma comment(lib,"opencv_viz2410d.lib")

//QT
#pragma comment(lib,"qtmaind.lib")
#pragma comment(lib,"Qt5Cored.lib")
#pragma comment(lib,"Qt5Guid.lib")
#pragma comment(lib,"Qt5PrintSupportd.lib")
#pragma comment(lib,"Qt5Widgetsd.lib")
#pragma comment(lib,"Qt5SerialPortd.lib")
#pragma comment(lib,"Qt5Networkd.lib")

#else 
#if USE_OPENCV
#pragma comment(lib,"opencv_calib3d2410.lib")
//#pragma comment(lib,"opencv_contrib2410.lib")
#pragma comment(lib,"opencv_core2410.lib")
#pragma comment(lib,"opencv_features2d2410.lib")
#pragma comment(lib,"opencv_flann2410.lib")
#pragma comment(lib,"opencv_gpu2410.lib")
#pragma comment(lib,"opencv_highgui2410.lib")
#pragma comment(lib,"opencv_imgproc2410.lib")
#pragma comment(lib,"opencv_legacy2410.lib")
#pragma comment(lib,"opencv_ml2410.lib")
#pragma comment(lib,"opencv_objdetect2410.lib")
#pragma comment(lib,"opencv_ts2410.lib")
#pragma comment(lib,"opencv_video2410.lib")
#pragma comment(lib,"opencv_nonfree2410.lib")
//#pragma comment(lib,"opencv_viz2410.lib")
#endif
//QT
#pragma comment(lib,"qtmain.lib")
#pragma comment(lib,"Qt5Core.lib")
#pragma comment(lib,"Qt5Gui.lib")
#pragma comment(lib,"Qt5PrintSupport.lib")
#pragma comment(lib,"Qt5Widgets.lib")
#pragma comment(lib,"Qt5SerialPort.lib")
#pragma comment(lib,"Qt5Network.lib")
#endif