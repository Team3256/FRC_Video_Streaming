/* GStreamer
 * Copyright (C) 2008 Wim Taymans <wim.taymans at gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

// modified to include 2 streams AND to read from settings.txt (see interactive.md in docs)
#include <gst/gst.h>

#include <gst/rtsp-server/rtsp-server.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFAULT_RTSP_PORT "8554"

static char *port = (char *) DEFAULT_RTSP_PORT;

static GOptionEntry entries[] = {
  {"port", 'p', 0, G_OPTION_ARG_STRING, &port,
      "Port to listen on (default: " DEFAULT_RTSP_PORT ")", "PORT"},
  {NULL}
};

char* gstCombiner (int cameraNumber, int frame)
{
  //int resHeight = resWidth * 16/9;
  //char height[10000];
  //sprintf(height, "%d", resHeight); //converting height to a string

  //char width[10000];
  //sprintf(width, "%d", resWidth); // convert width to a string

  char framerate[1000];
  sprintf(framerate, "%d", frame); // convert frame to string
  //resWidth = resolution width (ex: 640), resHeight = resolution height (ex: 360), frame = framerate

  char camera[100];
  sprintf(camera, "%d", cameraNumber);

  //ADDING CAMERANUMBER
  char* finalReturn = malloc(10000);
  strcat(finalReturn, "( v4l2src device=/dev/video");
  //char finalReturn[10000] = "( v4l2src device=/dev/video";
  strcat(finalReturn, camera);

  //ADDING WIDTH
  strcat(finalReturn,  " ! video/x-raw,width=426");
  //strcat(finalReturn, height);

  // ADDING HEIGHT
  strcat(finalReturn, ",height=240");
  //strcat(finalReturn, width);

  // ADDING FRAMERATE
  strcat(finalReturn, ",framerate=");
  strcat(finalReturn, framerate);
  strcat(finalReturn, "/1 ! videoconvert ! video/x-raw,format=I420 ! x264enc tune=zerolatency bitrate=600 threads=1 ! rtph264pay config-interval=1 name=pay0 pt=96 )");

  return finalReturn;
}

int
main (int argc, char *argv[])
{
  GMainLoop *loop;
  GstRTSPServer *server;
  GstRTSPMountPoints *mounts;
  GstRTSPMediaFactory *factory;
  GOptionContext *optctx;
  GError *error = NULL;

  optctx = g_option_context_new ("<launch line> - Test RTSP Server, Launch\n\n"
      "Example: \"( videotestsrc ! x264enc ! rtph264pay name=pay0 pt=96 )\"");
  g_option_context_add_main_entries (optctx, entries, NULL);
  g_option_context_add_group (optctx, gst_init_get_option_group ());
  if (!g_option_context_parse (optctx, &argc, &argv, &error)) {
    g_printerr ("Error parsing options: %s\n", error->message);
    g_option_context_free (optctx);
    g_clear_error (&error);
    return -1;
  }
  g_option_context_free (optctx);

  loop = g_main_loop_new (NULL, FALSE);

  /* create a server instance */
  server = gst_rtsp_server_new ();
  g_object_set (server, "service", port, NULL);

  /* get the mount points for this server, every server has a default object
   * that be used to map uri mount points to media factories */
  mounts = gst_rtsp_server_get_mount_points (server);

  /* make a media factory for a test stream. The default media factory can use
   * gst-launch syntax to create pipelines.
   * any launch line works as long as it contains elements named pay%d. Each
   * element with pay%d names will be a stream */

  // Please note that the video2 and video0 designations depend on how the system sees the two cameras. These numbers may need to be changed or swapped if the cameras are unplugged or if they change USB ports.
  // Curerntly these cameras are both plugged into the USB 2.0 ports on the Pi

  int inputFrame;
  FILE *fptr;

  fptr = fopen("/home/pi/interactive/settings.txt","r");   //CHANGE PATH BASED ON SETINGS FILE
  fscanf(fptr,"%d", &inputFrame);
  fclose(fptr);

  factory = gst_rtsp_media_factory_new ();
  gst_rtsp_media_factory_set_launch (factory, gstCombiner(2, inputFrame));
  gst_rtsp_media_factory_set_shared (factory, TRUE);
  gst_rtsp_mount_points_add_factory (mounts, "/front", factory);

  factory = gst_rtsp_media_factory_new ();
  gst_rtsp_media_factory_set_launch (factory, gstCombiner(0, inputFrame));
  gst_rtsp_media_factory_set_shared (factory, TRUE);
  gst_rtsp_mount_points_add_factory (mounts, "/top", factory);

  /* attach the test factory to the /test url */
  gst_rtsp_mount_points_add_factory (mounts, "/test", factory);

  /* don't need the ref to the mapper anymore */
  g_object_unref (mounts);

  /* attach the server to the default maincontext */
  gst_rtsp_server_attach (server, NULL);

  /* start serving */
  g_print ("stream ready at rtsp://127.0.0.1:%s/INSERT YOUR CAMERA NAMES\n", port);
  g_main_loop_run (loop);

  return 0;
}
