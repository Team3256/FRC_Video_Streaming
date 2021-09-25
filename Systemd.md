
### Automating GStreamer
We will be following this guide from 'A Guide to H.264 Streaming' under the section titled 'Sysetmd and services'.

Download the streaming.service file in the repo and place it in the /etc/systemd/system folder.
Then download the startstreaming.sh file and place it in your home directory. Make it executable by executing 'chmod u+x startstreaming.sh'.

Then run the following command to load the service fiels again:

    sudo systemctl daemon-reload
    
Then, start the service:

    sudo systemctl start streaming
    sudo systemctl enable streaming

If you run 'sudo systemctl status streaming', you should see that the service is running. You can run 'journalctl -u streaming' to see the full logs for the new service.

Doing this ensures that as soon as the pi boots, the camera stream is ready to use, with no commands or user input required.
