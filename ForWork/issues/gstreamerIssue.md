### ERROR: from element /GstPipeline:pipeline0/GstV4l2Src:v4l2src0: Internal data stream error.

Additional debug info:

../git/libs/gst/base/gstbasesrc.c(3127): gst_base_src_loop (): /GstPipeline:pipeline0/GstV4l2Src:v4l2src0:

Fix: the issue is introduced by adding "framerate=(fraction)30/1" in the capsfilter, remove this, the problem disappears.