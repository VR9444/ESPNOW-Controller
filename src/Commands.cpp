#include "Commands.h"
#include "FsManager.h"

namespace Commands
{
    Commands::Commands(SysData::SysData &sysData, FsManager &fsManager)
        : sysData(&sysData), fsManager(&fsManager)
    {
    }

    void Commands::readSticks()
    {
        readRawValues();
        sanitizeValues();
    }

    void Commands::readRawValues()
    {
        sysData->Commands.throttle_RAW = analogRead(THROTTLE_PIN);
        sysData->Commands.yaw_RAW = analogRead(YAW_PIN);
        sysData->Commands.pitch_RAW = analogRead(PITCH_PIN);
        sysData->Commands.roll_RAW = analogRead(ROLL_PIN);
    }

    void Commands::sanitizeValues()
    {
        sysData->Commands.roll_sanitized = Commands::processInput(sysData->Commands.roll_RAW,
                                                                  sysData->CommandsCalibration.roll_min,
                                                                  sysData->CommandsCalibration.roll_max,
                                                                  sysData->CommandsCalibration.roll_center,
                                                                  ROLL_INVERTED);

        sysData->Commands.pitch_sanitized = Commands::processInput(sysData->Commands.pitch_RAW,
                                                                   sysData->CommandsCalibration.pitch_min,
                                                                   sysData->CommandsCalibration.pitch_max,
                                                                   sysData->CommandsCalibration.pitch_center,
                                                                   PITCH_INVERTED);

        sysData->Commands.throttle_sanitized = Commands::processInput(sysData->Commands.throttle_RAW,
                                                                      sysData->CommandsCalibration.throttle_min,
                                                                      sysData->CommandsCalibration.throttle_max,
                                                                      sysData->CommandsCalibration.throttle_center,
                                                                      THROTTLE_INVERTED);

        sysData->Commands.yaw_sanitized = Commands::processInput(sysData->Commands.yaw_RAW,
                                                                 sysData->CommandsCalibration.yaw_min,
                                                                 sysData->CommandsCalibration.yaw_max,
                                                                 sysData->CommandsCalibration.yaw_center,
                                                                 YAW_INVERTED);
    }

    bool Commands::calibrateCenters()
    {
        Serial.println("Calibration starts in 10s. Move sticks to the center.");
        delay(10000);
        long roll_sum = 0, pitch_sum = 0, yaw_sum = 0, throttle_sum = 0;
        for (int i = 0; i < NUM_CALIBRATION_SAMPLES_CENTER; i++)
        {
            roll_sum += analogRead(ROLL_PIN);
            pitch_sum += analogRead(PITCH_PIN);
            yaw_sum += analogRead(YAW_PIN);
            throttle_sum += analogRead(THROTTLE_PIN);
            delay(10);
        }

        sysData->CommandsCalibration.roll_center = roll_sum / NUM_CALIBRATION_SAMPLES_CENTER;
        sysData->CommandsCalibration.pitch_center = pitch_sum / NUM_CALIBRATION_SAMPLES_CENTER;
        sysData->CommandsCalibration.yaw_center = yaw_sum / NUM_CALIBRATION_SAMPLES_CENTER;
        sysData->CommandsCalibration.throttle_center = throttle_sum / NUM_CALIBRATION_SAMPLES_CENTER;

        if (THROTTLE_INVERTED == -1)
        {
            sysData->CommandsCalibration.throttle_center = Commands::invertValueMap(sysData->CommandsCalibration.throttle_center, sysData->CommandsCalibration.throttle_min, sysData->CommandsCalibration.throttle_max);
        }

        if (YAW_INVERTED == -1)
        {
            sysData->CommandsCalibration.yaw_center = Commands::invertValueMap(sysData->CommandsCalibration.yaw_center, sysData->CommandsCalibration.yaw_min, sysData->CommandsCalibration.yaw_max);
        }

        if (PITCH_INVERTED == -1)
        {
            sysData->CommandsCalibration.pitch_center = Commands::invertValueMap(sysData->CommandsCalibration.pitch_center, sysData->CommandsCalibration.pitch_min, sysData->CommandsCalibration.pitch_max);
        }

        if (ROLL_INVERTED == -1)
        {
            sysData->CommandsCalibration.roll_center = Commands::invertValueMap(sysData->CommandsCalibration.roll_center, sysData->CommandsCalibration.roll_min, sysData->CommandsCalibration.roll_max);
        }

        Serial.println("Center calibration complete.");
        return fsManager->saveCalibration();
    }

    int Commands::invertValueMap(int raw_value, int min_value, int max_value)
    {
        return map(raw_value, min_value, max_value, max_value, min_value);
    }

    bool Commands::calibrateRanges()
    {
        Serial.println("Range calibration started! Move sticks in all directions.");
        sysData->CommandsCalibration.roll_min =
            sysData->CommandsCalibration.pitch_min =
                sysData->CommandsCalibration.yaw_min =
                    sysData->CommandsCalibration.throttle_min = 4095;

        sysData->CommandsCalibration.roll_max =
            sysData->CommandsCalibration.pitch_max =
                sysData->CommandsCalibration.yaw_max =
                    sysData->CommandsCalibration.throttle_max = 0;

        for (int i = 0; i < NUM_CALIBRATION_SAMPLES; i++)
        {
            int roll_val = analogRead(ROLL_PIN);
            int pitch_val = analogRead(PITCH_PIN);
            int yaw_val = analogRead(YAW_PIN);
            int throttle_val = analogRead(THROTTLE_PIN);

            sysData->CommandsCalibration.roll_min = min(sysData->CommandsCalibration.roll_min, roll_val);
            sysData->CommandsCalibration.roll_max = max(sysData->CommandsCalibration.roll_max, roll_val);

            sysData->CommandsCalibration.pitch_min = min(sysData->CommandsCalibration.pitch_min, pitch_val);
            sysData->CommandsCalibration.pitch_max = max(sysData->CommandsCalibration.pitch_max, pitch_val);

            sysData->CommandsCalibration.yaw_min = min(sysData->CommandsCalibration.yaw_min, yaw_val);
            sysData->CommandsCalibration.yaw_max = max(sysData->CommandsCalibration.yaw_max, yaw_val);

            sysData->CommandsCalibration.throttle_min = min(sysData->CommandsCalibration.throttle_min, throttle_val);
            sysData->CommandsCalibration.throttle_max = max(sysData->CommandsCalibration.throttle_max, throttle_val);

            delay(10);
        }

        Serial.println("Range calibration complete.");
        return fsManager->saveCalibration();
    }

    void Commands::finilizeCalibration()
    {
        Serial.println("Calibration Data:");
        Serial.print("Roll Center: ");
        Serial.println(sysData->CommandsCalibration.roll_center);
        Serial.print("Pitch Center: ");
        Serial.println(sysData->CommandsCalibration.pitch_center);
        Serial.print("Yaw Center: ");
        Serial.println(sysData->CommandsCalibration.yaw_center);
        Serial.print("Throttle Center: ");
        Serial.println(sysData->CommandsCalibration.throttle_center);

        Serial.print("Roll Min: ");
        Serial.println(sysData->CommandsCalibration.roll_min);
        Serial.print("Roll Max: ");
        Serial.println(sysData->CommandsCalibration.roll_max);
        Serial.print("Pitch Min: ");
        Serial.println(sysData->CommandsCalibration.pitch_min);
        Serial.print("Pitch Max: ");
        Serial.println(sysData->CommandsCalibration.pitch_max);
        Serial.print("Yaw Min: ");
        Serial.println(sysData->CommandsCalibration.yaw_min);
        Serial.print("Yaw Max: ");
        Serial.println(sysData->CommandsCalibration.yaw_max);
        Serial.print("Throttle Min: ");
        Serial.println(sysData->CommandsCalibration.throttle_min);
        Serial.print("Throttle Max: ");
        Serial.println(sysData->CommandsCalibration.throttle_max);
    }

    int Commands::processInput(int raw_value, int min_value, int max_value, int center, int inverted)
    {
        int processed_value;

        if (inverted == -1)
        {
            raw_value = Commands::invertValueMap(raw_value, min_value, max_value);
        }

        if (raw_value > center)
        {
            processed_value = map(raw_value, center, max_value, 1500, 2000);
        }
        else
        {
            processed_value = map(raw_value, min_value, center, 1000, 1500);
        }

        // Apply inversion correctly
        return processed_value;
    }
} // namespace CommandsCalibrate
