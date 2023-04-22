#pragma once

#define NETWORK_HOST "ekantica-railway.up.railway.app"
#define NETWORK_PATH "/data"

typedef struct {
    int temperature;
    int humidity;
    int moisture;
    int water_level;
    int uv_index;
    int visible_light;
} network_data_t;

void network_init(void);
int network_send_request(network_data_t params);
