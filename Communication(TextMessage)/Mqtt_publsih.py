# MQTT Publish Demo
# Publish two messages, to two different topics

import paho.mqtt.publish as publish

msg ='{"payload":"Dear Teacher, You have assigned period 3 in 10A","number":"+94763475089"}'
publish.single("Dilun/test",msg, hostname="Broker.mqttdashboard.com")

print("Done")
