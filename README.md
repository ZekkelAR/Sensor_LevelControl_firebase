# Sensor_LevelControl_firebase
code of sensor potential hydrogen and level control with NodeMCU8266

## Change this string

```
define FIREBASE_HOST "Your Firebase Host"
define FIREBASE_AUTH "Your firebase Auth"
define WIFI_SSID "name wifi"
define WIFI_PASSWORD "password wifi"
```

## Change this child firebase with your child
```
Firebase.setString("/DATA/SENSOR_LEVEL", String(distance));  
fireStatus = Firebase.getInt("/DATA/PUMP_ONE");
```


