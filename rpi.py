import serial
import time
import paho.mqtt.client as mqtt

broker = "broker.hivemq.com"
topic = "robot/environment"

client = mqtt.Client()
client.connect(broker, 1883, 60)

env_serial = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
gps_serial = serial.Serial('/dev/ttyUSB1', 9600, timeout=1)
time.sleep(2)

def parse_env_data(line):
    try:
        parts = line.strip().split(',')
        data = {}
        for part in parts:
            key, value = part.split(':')
            data[key] = float(value)
        return data
    except:
        return None

def get_gps_coordinates(line):
    try:
        if "$GPGGA" in line:
            parts = line.split(",")
            lat = float(parts[2])
            lat_dir = parts[3]
            lon = float(parts[4])
            lon_dir = parts[5]

            lat_deg = int(lat / 100)
            lat_min = lat - (lat_deg * 100)
            latitude = lat_deg + (lat_min / 60.0)
            if lat_dir == 'S':
                latitude *= -1

            lon_deg = int(lon / 100)
            lon_min = lon - (lon_deg * 100)
            longitude = lon_deg + (lon_min / 60.0)
            if lon_dir == 'W':
                longitude *= -1

            return round(latitude, 6), round(longitude, 6)
    except:
        return None, None
    return None, None

while True:
    env_data = None
    gps_data = None

    if env_serial.in_waiting:
        line = env_serial.readline().decode('utf-8')
        env_data = parse_env_data(line)

    if gps_serial.in_waiting:
        line = gps_serial.readline().decode('utf-8')
        lat, lon = get_gps_coordinates(line)
        gps_data = {"LAT": lat, "LON": lon} if lat and lon else None

    if env_data:
        if gps_data:
            env_data.update(gps_data)
        print(env_data)
        client.publish(topic, str(env_data))
