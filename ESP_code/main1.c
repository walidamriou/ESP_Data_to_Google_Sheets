#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_http_client.h"

#define MAX_HTTP_RECV_BUFFER 512

//Wifi informarion
#define WIFI_SSID "your_wifi_ssid_here"
#define WIFI_PASS "your_wifi_password_here"

//Google sheets informarion
#define SPREADSHEET_ID "your_spreadsheet_script_id_here" 
//note if you use data_from_esp32.ods sheets file use this:
#define URL "https://script.google.com/macros/s/"SPREADSHEET_ID"/exec?id=data_s_1&data1=10&data2=20&data3=30&data4=40"

/* 

if you use other sheet structure change he queries 
#define URL "https://script.google.com/macros/s/"SPREADSHEET_ID"/exec?your_queries_here
If you need to know more about how you choose queries, go to google apps scriptes in the github
project : https://github.com/walidamriou/ESP_Data_to_Google_Sheets/blob/master/Google_apps_scripts/script1.gs 

*/

static void initialise_wifi(void);
static esp_err_t event_handler(void *ctx, system_event_t *event);
esp_err_t _http_event_handler(esp_http_client_event_t *evt);
static void trigger_http_request(const char *url);
static void http_request_task(void *pvParameters);

/* FreeRTOS event group to signal when we are connected & ready to make a request */
static EventGroupHandle_t wifi_event_group;

/* The event group allows multiple bits for each event,
   but we only care about one event - are we connected
   to the AP with an IP? */
const int CONNECTED_BIT = BIT0;

static const char *TAG = "esp32-spreadsheet-demo";

/* @brief: Function to initialise WiFi
 * @param:
 * @retval: 
*/
static void initialise_wifi(void)
{
    tcpip_adapter_init();
    wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
        },
    };
    ESP_LOGI(TAG, "Setting WiFi configuration SSID %s...", wifi_config.sta.ssid);
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK( esp_wifi_start() );
}

/* @brief: The system callback function
 * @param:
 * @retval: 
*/
static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        /* This is a workaround as ESP32 WiFi libs don't currently
           auto-reassociate. */
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
        break;
    default:
        break;
    }
    return ESP_OK;
}

/* @brief: The HTTP callback function
 * @param: evt, HTTP Client events data
 * @retval: 
*/
esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            if (!esp_http_client_is_chunked_response(evt->client)) {
                // Write out data
                // printf("%.*s", evt->data_len, (char*)evt->data);
            }

            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
            break;
    }
    return ESP_OK;
}

/* @brief: Function to trigger an HTTP request
 * @param: url, the URL to which an HTTP request is to be sent
 * @retval: 
*/
static void trigger_http_request(const char *url)
{
    /* Wait for the callback to set the CONNECTED_BIT in the
           event group.
        */
    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT,
                        false, true, portMAX_DELAY);
    ESP_LOGI(TAG, "Connected to AP");

    esp_http_client_config_t config = {
        .url = url,
        .event_handler = _http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);

    // GET
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "HTTP GET Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(TAG, "HTTP GET request failed: %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
}

/* @brief: Task that hits an HTTP request every 5 secs
 * @param:
 * @retval: 
*/
static void http_request_task(void *pvParameters)
{
    while (1) {
        trigger_http_request(URL);
        vTaskDelay(5000/portTICK_PERIOD_MS);
    }
}

/* @brief: Application execution starts from here
 * @param:
 * @retval:
*/
void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    
    initialise_wifi();
    
    xTaskCreate(&http_request_task, "http_request_task", 10240, NULL, 5, NULL);
}