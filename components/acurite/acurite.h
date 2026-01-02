#pragma once

#include "esphome/components/remote_receiver/remote_receiver.h"
#include <cstdint>
#include <vector>

namespace esphome {
namespace acurite {

class AcuRiteDevice {
 public:
  virtual void update_battery(uint8_t value) {}
  virtual void update_speed(float value) {}
  virtual void update_direction(float value) {}
  virtual void update_temperature(float value) {}
  virtual void update_humidity(float value) {}
  virtual void update_distance(float value) {}
  virtual void update_rainfall(uint32_t count) {}
  virtual void update_lightning(uint32_t count) {}
  virtual void update_uv(float value) {}
  virtual void update_lux(float value) {}

  void set_id(uint16_t id) { this->id_ = id; }
  uint16_t get_id() const { return this->id_; }

  void set_zero_duration(uint32_t zero_duration) { zero_duration_ = zero_duration; }
  uint32_t get_zero_duration() const { return zero_duration_; }

  void set_one_duration(uint32_t one_duration) { one_duration_ = one_duration; }
  uint32_t get_one_duration() const { return one_duration_; }

  void set_sync_duration(uint32_t sync_duration) { sync_duration_ = sync_duration; }
  uint32_t get_sync_duration() const { return sync_duration_; }

  void set_sync_count(uint8_t sync_count) { sync_count_ = sync_count; }
  uint8_t get_sync_count() const { return sync_count_; }

 protected:
  uint16_t id_{0};
  uint32_t zero_duration_{200};  // duration in us
  uint32_t one_duration_{400};  // duration in us
  uint32_t sync_duration_{600};  // duration in us
  uint8_t sync_count_{4};
};

class AcuRiteComponent : public Component, public remote_base::RemoteReceiverListener {
 public:
  void add_device(AcuRiteDevice *dev, uint16_t id) { this->devices_.push_back(dev); }
  bool on_receive(remote_base::RemoteReceiveData data) override;

 protected:
  void decode_temperature_(AcuRiteDevice* device, uint8_t *data, uint8_t len);
  void decode_rainfall_(AcuRiteDevice* device, uint8_t *data, uint8_t len);
  void decode_lightning_(AcuRiteDevice* device, uint8_t *data, uint8_t len);
  void decode_atlas_(AcuRiteDevice* device, uint8_t *data, uint8_t len);
  void decode_notos_(AcuRiteDevice* device, uint8_t *data, uint8_t len);
  void decode_iris_(AcuRiteDevice* device, uint8_t *data, uint8_t len);
  void decode_515_(AcuRiteDevice* device, uint8_t *data, uint8_t len);
  void decode_986_(AcuRiteDevice* device, uint8_t *data, uint8_t len);

  bool validate_(uint8_t *data, uint8_t len, int8_t except);
  uint8_t crc8le_(uint8_t *data, uint8_t len, uint8_t poly) const;
  uint8_t reverse8_(uint8_t data) const;
  std::vector<AcuRiteDevice *> devices_;
};

}  // namespace acurite
}  // namespace esphome
