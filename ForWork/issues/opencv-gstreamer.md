# opencv-4.5.2 not support multiplanar, the support just added in opencv-4.7.0
[ WARN:0] global /tmp/pip-req-build-4nusm4mm/opencv/modules/videoio/src/cap_gstreamer.cpp (1825) handleMessage OpenCV | GStreamer warning: Embedded video playback halted; module v4l2src0 reported: Failed to allocate required memory.
[ WARN:0] global /tmp/pip-req-build-4nusm4mm/opencv/modules/videoio/src/cap_gstreamer.cpp (914) open OpenCV | GStreamer warning: unable to start pipeline
[ WARN:0] global /tmp/pip-req-build-4nusm4mm/opencv/modules/videoio/src/cap_gstreamer.cpp (501) isPipelinePlaying OpenCV | GStreamer warning: GStreamer: pipeline have not been created
[ WARN:0] global /tmp/pip-req-build-4nusm4mm/opencv/modules/videoio/src/cap_v4l.cpp (893) open VIDEOIO(V4L2:/dev/video0): can't open camera by index

When enabling the debug information with:
- export OPENCV_LOG_LEVEL=DEBUG
- export OPENCV_VIDEOIO_DEBUG=1
More detailed information is observed:
not supported - device is unable to capture video (missing V4L2_CAP_VIDEO_CAPTURE)

# videoio_gstreamer library not found
[ INFO:0@0.005] global videoio_registry.cpp:232 VideoBackendRegistry VIDEOIO: Enabled backends(8, sorted by priority): FFMPEG(1000); GSTREAMER(990); INTEL_MFX(980); V4L2(970); CV_IMAGES(960); CV_MJPEG(950); UEYE(940); OBSENSOR(930)
[ WARN:0@0.005] global cap.cpp:130 open VIDEOIO(GSTREAMER): trying capture filename='v4l2src device=/dev/video0 ! video/x-raw,width=320,height=240,format=GRAY8 ! videoconvert ! video/x-raw,width=320,height=240 ! appsink' ...
[ INFO:0@0.005] global backend_plugin.cpp:369 getPluginCandidates VideoIO plugin (GSTREAMER): glob is 'libopencv_videoio_gstreamer*.so', 1 location(s)
[ INFO:0@0.017] global backend_plugin.cpp:379 getPluginCandidates     - /usr/lib: 0
[ INFO:0@0.018] global backend_plugin.cpp:383 getPluginCandidates Found 0 plugin(s) for GSTREAMER
[ WARN:0@0.018] global cap.cpp:190 open VIDEOIO(GSTREAMER): backend is not available (plugin is missing, or can't be loaded due dependencies or it is not compatible)


# undefined reference  to
/usr/lib/gcc/aarch64-poky-linux/10.2.0/../../../../aarch64-poky-linux/bin/ld: CMakeFiles/opencv_videoio.dir/src/cap_gstreamer.cpp.o: in function `void cv::(anonymous namespace)::GSafePtr_release<_GstElement>(_GstElement**)':
cap_gstreamer.cpp:(.text._ZN2cv12_GLOBAL__N_1L16GSafePtr_releaseI11_GstElementEEvPPT_+0x10): undefined reference to `g_type_check_instance_cast'


# ld: cannot find -lgstreamer-1.0


# DC1394 not found
/home/alan/V4L2/opencv-4.7.0/modules/videoio/src/cap_dc1394_v2.cpp:59:10: fatal error: dc1394/dc1394.h: No such file or directory

Disable it with -DWITH_1394=OFF

# Imported target "GTest::GTest" includes non-existent path
Error : Make Error in modules/videoio/CMakeLists.txt:
Imported target “ocv.3rdparty.gstreamer” includes non-existent path
 "/usr/include/orc-0.4"

 Fix: cp the orc-0.4 directory from gstreamer install directory to /usr/include




 # caps not compatible

 0:00:00.080638000  1285     0x21a9cf60 WARN                GST_CAPS gstpad.c:3235:gst_pad_query_accept_caps_default:<h265enc:sink> caps: video/x-raw, width=(int)320, height=(int)240, format=(string)I420 were not compatible with: video/x-raw, width=(int)320, height=(int)240, framerate=(fraction)[ 0/1, 2147483647/1 ], format=(string)I420

Fix: Add "framerate=(fraction)30/1" to caps


# invalid buffer size
0:00:00.131391125  1336[13149.573384] audit: type=1701 audit(1616594663.816:19): auid=4294967295 uid=0 gid=0 ses=4294967295 pid=1336 comm="source:src" exe="/home/root/v4l2Capture" sig=11 res=1

[13149.583912] mxc-mipi-csi2.0: mipi_csis_s_stream: 0, state: 0x0

[13149.596900] mxc-mipi-csi2.0: mipi_csis_s_stream, Sensor stream DIS =====

[13149.603615] enter atom320_s_stream DIS

[13149.607398] enter atom320_poll_init_completed

     0x2e435f60 ERROR  13149.613599]  atom320_read_reg 0x8084:0x01(1)

[13149.619190] atom320_poll_init_completed Sensor init completed (9)

00m              default video-frame.c:181:gst_video_frame_map_id: invalid buffer size 44 < 115200



# Invalid read of size 8
==1459== Invalid read of size 8
==1459==    at 0x60C07A8: gst_allocator_alloc (in /usr/lib/libgstreamer-1.0.so.0.1805.0)
==1459==    by 0x60CC423: gst_buffer_new_allocate (in /usr/lib/libgstreamer-1.0.so.0.1805.0)
==1459==    by 0x728F3C7: gst_video_encoder_allocate_output_buffer (in /usr/lib/libgstvideo-1.0.so.0.1805.0)
==1459==    by 0xB856263: ??? (in /usr/lib/gstreamer-1.0/libgstvpu.so)
==1459==    by 0x728CB43: ??? (in /usr/lib/libgstvideo-1.0.so.0.1805.0)
==1459==    by 0x610CB67: ??? (in /usr/lib/libgstreamer-1.0.so.0.1805.0)
==1459==    by 0x610E9D7: ??? (in /usr/lib/libgstreamer-1.0.so.0.1805.0)
==1459==    by 0x6116507: gst_pad_push (in /usr/lib/libgstreamer-1.0.so.0.1805.0)
==1459==    by 0x603954B: ??? (in /usr/lib/libgstbase-1.0.so.0.1805.0)
==1459==    by 0x6149123: ??? (in /usr/lib/libgstreamer-1.0.so.0.1805.0)
==1459==    by 0x62E4B67: ??? (in /usr/lib/libglib-2.0.so.0.6600.7)
==1459==    by 0x62E4083: ??? (in /usr/lib/libglib-2.0.so.0.6600.7)
==1459==  Address 0xb8 is not stack'd, malloc'd or (recently) free'd
==1459==
==1459==
==1459== Process terminating with default action of signal 11 (SIGSEGV)
==1459==  Access not within mapped region at address 0xB8


# GDB: 0xfffff1437000 <error: Cannot access memory at address 0xfffff1437000>
Reason: [Examining mmaped addresses using GDB](https://stackoverflow.com/questions/654393/examining-mmaped-addresses-using-gdb/7558859#7558859)