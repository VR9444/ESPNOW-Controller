#include "NOWhelper.h"

void Tasks::NOWhelper::printMacAdress()
{
    uint8_t ownMacAddress[6];
    WiFi.macAddress(ownMacAddress); // Get the MAC address of the ESP32 in Station mode
    Serial.print("Own MAC Address: ");
    for (int i = 0; i < 6; i++)
    {
        if (ownMacAddress[i] < 0x10)
        {
            Serial.print("0"); // Print leading zero for single-digit hex
        }
        Serial.print(ownMacAddress[i], HEX); // Print each byte in hexadecimal
        if (i < 5)
        {
            Serial.print(":"); // Separate bytes with colon
        }
    }
    Serial.println(); // Newline after the address
}

bool Tasks::NOWhelper::initESPNOW()
{
    esp_netif_init();

    // Initialize the Wi-Fi driver
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_err_t wifiInitResult = esp_wifi_init(&cfg);
    if (wifiInitResult != ESP_OK)
    {
        Serial.printf("Failed to initialize Wi-Fi. Error code: %d\n", wifiInitResult);
        return false;
    }

    // Set Wi-Fi mode to Station
    esp_err_t wifiModeResult = esp_wifi_set_mode(WIFI_MODE_STA);
    if (wifiModeResult != ESP_OK)
    {
        Serial.printf("Failed to set Wi-Fi mode. Error code: %d\n", wifiModeResult);
        return false;
    }

    // Start Wi-Fi
    esp_err_t wifiStartResult = esp_wifi_start();
    if (wifiStartResult != ESP_OK)
    {
        Serial.printf("Failed to start Wi-Fi. Error code: %d\n", wifiStartResult);
        return false;
    }

    // Enable Long Range (LR) mode

    esp_err_t resultProtocol = esp_wifi_set_protocol(WIFI_IF_STA, WIFI_PROTOCOL_LR);
    if (resultProtocol == ESP_OK)
    {
        Serial.println("Long Range (LR) mode enabled.");
    }
    else
    {
        Serial.printf("Failed to enable Long Range mode. Error code: %d\n", resultProtocol);
        return false;
    }
    // Initialize ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("ESP-NOW initialization failed");
        return false;
    }

    // Add peer
    esp_now_peer_info_t peerInfo;

    // Zero initialize the peerInfo structure to avoid uninitialized values
    memset(&peerInfo, 0, sizeof(peerInfo));

    // Copy the MAC address into the peer structure
    memcpy(peerInfo.peer_addr, RECEIVER_MAC, sizeof(RECEIVER_MAC));

    // Set the channel (make sure the channel matches between both devices)
    peerInfo.channel = 0;     // Use default channel
    peerInfo.encrypt = false; // No encryption

    esp_err_t result = esp_now_add_peer(&peerInfo);

    // Handle errors based on the result
    if (result != ESP_OK)
    {
        Serial.print("Failed to add peer. Error code: ");
        Serial.println(result);

        if (result == ESP_ERR_ESPNOW_NOT_INIT)
        {
            Serial.println("ESPNOW is not initialized. Please call esp_now_init() first.");
        }
        else if (result == ESP_ERR_ESPNOW_ARG)
        {
            Serial.println("Invalid argument passed to esp_now_add_peer(). Check the peerInfo structure.");
        }
        else if (result == ESP_ERR_ESPNOW_FULL)
        {
            Serial.println("Peer list is full. Try removing a peer or increase the peer list size.");
        }
        else if (result == ESP_ERR_ESPNOW_NO_MEM)
        {
            Serial.println("Out of memory. Make sure your ESP32 has enough memory.");
        }
        else if (result == ESP_ERR_ESPNOW_EXIST)
        {
            Serial.println("The peer already exists in the peer list.");
        }
        else
        {
            Serial.println("Unknown error occurred.");
        }

        return false;
    }

    return true;
}