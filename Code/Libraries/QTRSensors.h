/*
 * QTRSensors.h
 *
 *  Created on: Aug 1, 2022
 *      Author: phang
 */

#ifndef QTRSENSORS_H_
#define QTRSENSORS_H_

#pragma once

#include "stdint.h"
#include "stdbool.h"

enum class QTRReadMode {
  Off,
  On,
  OnAndOff,
  OddEven,
  OddEvenAndOff,
  Manual
};

/// Sensor types.
enum class QTRType {
  Undefined,
  RC,
  Analog
};

/// Emitters selected to turn on or off.
enum class QTREmitters {
  All,
  Odd,
  Even,
  None
};

const uint8_t QTRNoEmitterPin = 255;

const uint16_t QTRRCDefaultTimeout = 2500;

const uint8_t QTRMaxSensors = 31;

class QTRSensors
{
  public:

    QTRSensors() = default;

    ~QTRSensors();

    void setTypeRC();

    void setTypeAnalog();

    QTRType getType() { return _type; }

    void setSensorPins(const uint8_t * pins, uint8_t sensorCount);

    void setTimeout(uint16_t timeout);

    uint16_t getTimeout() { return _timeout; }

    void setSamplesPerSensor(uint8_t samples);

    uint16_t getSamplesPerSensor() { return _samplesPerSensor; }

    void setEmitterPin(uint8_t emitterPin);

    void setEmitterPins(uint8_t oddEmitterPin, uint8_t evenEmitterPin);

    void releaseEmitterPins();

    uint8_t getEmitterPinCount() { return _emitterPinCount; }

    uint8_t getEmitterPin() { return _oddEmitterPin; }

    uint8_t getOddEmitterPin() { return _oddEmitterPin; }

    uint8_t getEvenEmitterPin()  { return _evenEmitterPin; }

    void setDimmable() { _dimmable = true; }

    void setNonDimmable() { _dimmable = false; }

    bool getDimmable() { return _dimmable; }

    void setDimmingLevel(uint8_t dimmingLevel);

    uint8_t getDimmingLevel() { return _dimmingLevel; }

    void emittersOff(QTREmitters emitters = QTREmitters::All, bool wait = true);

    void emittersOn(QTREmitters emitters = QTREmitters::All, bool wait = true);

    void emittersSelect(QTREmitters emitters);

    void calibrate(QTRReadMode mode = QTRReadMode::On);

    void resetCalibration();

    void read(uint16_t * sensorValues, QTRReadMode mode = QTRReadMode::On);

    void readCalibrated(uint16_t * sensorValues, QTRReadMode mode = QTRReadMode::On);

    uint16_t readLineBlack(uint16_t * sensorValues, QTRReadMode mode = QTRReadMode::On)
    {
      return readLinePrivate(sensorValues, mode, false);
    }

    uint16_t readLineWhite(uint16_t * sensorValues, QTRReadMode mode = QTRReadMode::On)
    {
      return readLinePrivate(sensorValues, mode, true);
    }

    struct CalibrationData
    {
      bool initialized = false;

      uint16_t * minimum = nullptr;

      uint16_t * maximum = nullptr;
    };

    CalibrationData calibrationOn;


    CalibrationData calibrationOff;


  private:

    uint16_t emittersOnWithPin(uint8_t pin);

    void calibrateOnOrOff(CalibrationData & calibration, QTRReadMode mode);

    void readPrivate(uint16_t * sensorValues, uint8_t start = 0, uint8_t step = 1);

    uint16_t readLinePrivate(uint16_t * sensorValues, QTRReadMode mode, bool invertReadings);

    QTRType _type = QTRType::Undefined;

    uint8_t * _sensorPins = nullptr;
    uint8_t _sensorCount = 0;

    uint16_t _timeout = QTRRCDefaultTimeout; // only used for RC sensors
    uint16_t _maxValue = QTRRCDefaultTimeout; // the maximum value returned by readPrivate()
    uint8_t _samplesPerSensor = 4; // only used for analog sensors

    uint8_t _oddEmitterPin = QTRNoEmitterPin; // also used for single emitter pin
    uint8_t _evenEmitterPin = QTRNoEmitterPin;
    uint8_t _emitterPinCount = 0;

    bool _dimmable = true;
    uint8_t _dimmingLevel = 0;

    uint16_t _lastPosition = 0;
};


#endif /* QTRSENSORS_H_ */
