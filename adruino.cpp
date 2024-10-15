/*
    The code is pretty simple. It connects to the Wi-Fi network, fetches audio data from the server,
    and then displays the predicted audio on the OLED display.
    The  fetchAudioFromServer  function sends an HTTP GET request to the server
    and reads the audio data from the response.
    The audio data is stored in the  audioBuffer  array.
    The  displayText  function displays the predicted audio on the OLED display.
    The  classifyAudio  function should predict the audio file based on the audio data.
    However, this function is not implemented in this example.
    The  setup  function initializes the OLED display and connects to the Wi-Fi network.
    The  loop  function fetches and classifies audio data every 5 seconds
    (depending on the  interval  variable).
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASS ""

#define HTTP_DOMAIN "" // Put the port forwared IP here
#define HTTP_ENDPOINT_SUFFIX "random"
#define HTTP_ENDPOINT HTTP_DOMAIN HTTP_ENDPOINT_SUFFIX
#define HTTP_PORT 5000

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Buffer to store the audio data
const int bufferSize = 1024; // 512KB
uint8_t audioBuffer[bufferSize];

// Refresh Interval for a new guess
int interval = 5000; // every 5 secs

// Function to connect to Wi-Fi
void connectToWiFi()
{
    Serial.print("Connecting to Wi-Fi");
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi");
}

// Function to fetch random audio from the server
bool fetchAudioFromServer()
{
    HTTPClient http;
    http.begin(HTTP_ENDPOINT);
    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK)
    {
        // Read the audio data from the response
        WiFiClient *stream = http.getStreamPtr();
        int contentLength = http.getSize();

        if (contentLength > 0)
        {
            int bytesRead = 0;
            while (http.connected() && (contentLength > 0 || contentLength == -1))
            {
                size_t size = stream->available();
                if (size)
                {
                    int len = stream->readBytes(audioBuffer + bytesRead, ((size > sizeof(audioBuffer)) ? sizeof(audioBuffer) : size));
                    bytesRead += len;
                    contentLength -= len;
                }
            }
            Serial.println("Audio data fetched");
            http.end();
            return true;
        }
    }
    else
    {
        Serial.printf("Error fetching audio: %d\n", httpCode);
    }

    http.end();
    return false;
}

// Function to display text on the OLED display
void displayText(const char *label)
{
    display.clearDisplay();
    display.setTextSize(2);      // Normal 1:1 pixel scale
    display.setTextColor(WHITE); // Draw white text
    display.setCursor(0, 0);     // Start at top-left corner
    display.print("Predicted:");
    display.setCursor(0, 30);
    display.print(label);
    display.display(); // Display text
}

void classifyAudio()
{
    // this should predict the audio file
    Serial.println("Prediction not implemedted");
}

void setup()
{
    Serial.begin(115200);

    // Initialize the OLED display
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("SSD1306 allocation failed");
        for (;;)
            ; // Don't proceed, loop forever
    }
    display.clearDisplay();
    display.display();

    // Connect to Wi-Fi
    connectToWiFi();
}

void loop()
{
    // Fetch and classify audio data every 5 seconds
    if (fetchAudioFromServer())
    {
        classifyAudio();
    }
    else
    {
        Serial.println("Failed to fetch audio");
    }

    // Wait 5 seconds before repeating
    delay(interval);
}
