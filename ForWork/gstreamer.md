# Video stream fetch flow with a gstreamer pipeline
- rtspsrc: connect rtsp server, fetch RTP package. All this follows RFC2326
- rtph264depay: extract H264 package from the RTP package. All this follows RFC3984
- mpegtsmux: pack mpeg stream into TS package
[Here]() is the flow pipeline.

[基于Gstreamer的实时视频流的分发](https://blog.csdn.net/sdjhs/article/details/51444934?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-51444934-blog-90032652.235%5Ev36%5Epc_relevant_default_base&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-51444934-blog-90032652.235%5Ev36%5Epc_relevant_default_base&utm_relevant_index=1)

[RTSP服务器，支持传输H.264和AAC格式的音视频](https://github.com/ImSjt/RtspServer)


# How to merge audio and video stream?
[Gstreamer USB摄像头音视频AVI文件合成与rtmp推流](https://blog.csdn.net/zhaoyun_zzz/article/details/93096902)
[GStreamer appsrc 等插件实现视频音频混流，录制和推流](https://blog.csdn.net/wowocpp/article/details/126360092)

# How can two elements be linked together?
为了将两个element链接在一起，它们必须共享一个公共的Caps子集（否则它们不可能相互理解）。这是Caps的主要目标。