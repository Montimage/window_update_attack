#include <stdio.h>
#include <nghttp2/nghttp2.h>


int main(void)
{
    // Initialize the nghttp2 library
    nghttp2_session *session;
    nghttp2_session_callbacks *callbacks;
    nghttp2_session_callbacks_new(&callbacks);
    nghttp2_session_client_new(&session, callbacks, NULL);
    
    // Send the WINDOW_UPDATE frame on stream 0 with a fixed window size increment value of 4096 bytes
    uint8_t window_update_frame[13] = {0x00, 0x00, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00};
    ssize_t rv = nghttp2_session_mem_send(session,(const uint8_t**) window_update_frame);

    // Check for errors
    if (rv != 13) {
        fprintf(stderr, "Error sending WINDOW_UPDATE frame: %s\n", nghttp2_strerror((int) rv));
    }

    // Cleanup
    nghttp2_session_del(session);
    nghttp2_session_callbacks_del(callbacks);

    return 0;
}
