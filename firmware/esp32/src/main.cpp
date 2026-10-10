#include <Arduino.h>
#include <math.h>
#include "driver/i2s.h"

// PIR sensor
constexpr int PIR_PIN = 27;

// MAX98357A I2S pins
constexpr int I2S_BCLK = 26;
constexpr int I2S_LRC  = 25;
constexpr int I2S_DOUT = 22;

constexpr i2s_port_t I2S_PORT = I2S_NUM_0;

bool previousMotion = false;

// Configure I2S output
bool initializeI2S() {
    i2s_config_t config = {};
    config.mode = (i2s_mode_t)(
        I2S_MODE_MASTER | I2S_MODE_TX
    );
    config.sample_rate = 16000;
    config.bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT;
    config.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT;
    config.communication_format = I2S_COMM_FORMAT_STAND_I2S;
    config.intr_alloc_flags = 0;
    config.dma_buf_count = 8;
    config.dma_buf_len = 256;
    config.use_apll = false;
    config.tx_desc_auto_clear = true;
    config.fixed_mclk = 0;

    esp_err_t err = i2s_driver_install(
        I2S_PORT, &config, 0, nullptr
    );

    if (err != ESP_OK) {
        Serial.printf(
            "I2S driver error: %s\n",
            esp_err_to_name(err)
        );
        return false;
    }

    i2s_pin_config_t pins = {};
    pins.bck_io_num = I2S_BCLK;
    pins.ws_io_num = I2S_LRC;
    pins.data_out_num = I2S_DOUT;
    pins.data_in_num = I2S_PIN_NO_CHANGE;

    err = i2s_set_pin(I2S_PORT, &pins);

    if (err != ESP_OK) {
        Serial.printf(
            "I2S pin error: %s\n",
            esp_err_to_name(err)
        );
        i2s_driver_uninstall(I2S_PORT);
        return false;
    }

    i2s_zero_dma_buffer(I2S_PORT);
    return true;
}

// Generate one test tone.
// This tests the amplifier and speaker, not speech playback.
void playTone(float frequency, int durationMs) {
    constexpr int sampleRate = 16000;
    constexpr int samplesPerBlock = 256;

    int16_t samples[samplesPerBlock * 2];

    int totalSamples = sampleRate * durationMs / 1000;
    int generated = 0;

    while (generated < totalSamples) {
        int count = min(
            samplesPerBlock,
            totalSamples - generated
        );

        for (int i = 0; i < count; i++) {
            float t = float(generated + i) / sampleRate;

            // Low-volume sine wave to start safely
            int16_t sample = (int16_t)(
                5000.0f * sinf(2.0f * PI * frequency * t)
            );

            // Stereo: duplicate the sample to both channels
            samples[i * 2] = sample;
            samples[i * 2 + 1] = sample;
        }

        size_t bytesWritten = 0;

        esp_err_t err = i2s_write(
            I2S_PORT,
            samples,
            count * 2 * sizeof(int16_t),
            &bytesWritten,
            portMAX_DELAY
        );

        if (err != ESP_OK) {
            Serial.printf(
                "I2S write error: %s\n",
                esp_err_to_name(err)
            );
            return;
        }

        generated += count;
    }
}

void playTestSound() {
    Serial.println("Playing speaker test...");

    playTone(600, 180);
    delay(80);

    playTone(800, 180);
    delay(80);

    playTone(1000, 250);

    // Clear remaining audio and stop transmitting.
    i2s_zero_dma_buffer(I2S_PORT);

    Serial.println("Speaker test finished.");
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    pinMode(PIR_PIN, INPUT);

    Serial.println();
    Serial.println("Smart Exit Reminder");
    Serial.println("Initializing I2S...");

    if (!initializeI2S()) {
        Serial.println("I2S initialization failed.");
        while (true) {
            delay(1000);
        }
    }

    Serial.println("I2S initialized.");
    Serial.println("Waiting for motion...");
}

void loop() {
    bool currentMotion = digitalRead(PIR_PIN) == HIGH;

    // Play once when motion changes from LOW to HIGH.
    if (currentMotion && !previousMotion) {
        Serial.println("Motion detected!");
        playTestSound();
    }

    if (!currentMotion && previousMotion) {
        Serial.println("Motion ended.");
    }

    previousMotion = currentMotion;

    delay(20);
}
