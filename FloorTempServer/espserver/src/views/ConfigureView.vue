<script setup lang="ts">

import { ref, reactive, onMounted } from 'vue'
import axios from 'axios'

interface ConfigureViewData {
    cfg: Config;
}
interface Config{
    hotspot: HotspotConfig,
    wifi: WifiConfig,
    mqtt: MqttConfig,
    floorControl: FloorControlConfig
    
}

interface HotspotConfig {
    name:string,
    ip: string,
    mask: string,
    login: string,
    password: string,
}
interface WifiConfig {
    ssid: string,
    password: string
}
interface MqttConfig{
    serverPath: string,
    username: string,
    password: string,
    port: Number
}

interface FloorControlConfig{
    temperatureTopic: string,
    tapTopic: string,
    minTemperature: Number,
    maxTemperature: Number
};




var data:ConfigureViewData =  reactive({
    cfg:{
        hotspot: {
            name: "",
            ip: "",
            mask: "",
            login: "",
            password: ""
        },
        wifi: {
            ssid: "",
            password: ""
        },
        mqtt: {
            serverPath:"",
            username: "",
            password: "",
            port: 0
        },
        floorControl: {
            temperatureTopic:"",
            tapTopic: "",
            minTemperature: 20,
            maxTemperature: 30
        }
    }
});

var isInProgress = ref(false);
var isDataUpdated = ref(false);

onMounted(() => {
    isInProgress.value = true;
  axios.get('/api/config')
  .then(function (response) {
    // handle success
    console.log(response);
    data.cfg = reactive(response.data);
  })
  .catch(function (error) {
    // handle error`
    console.log(error);
  })
  .finally(function () {
    // always executed
    isInProgress.value = false;
  });
})

function saveConfig() {
    isInProgress.value = true;
  axios({
  method: 'post',
  url: '/api/config/save',
  data: data.cfg
  }).then(function (response) {
    // handle success
    console.log(response);
    isDataUpdated.value = true;
   // data.cfg = reactive(response.data);
  })
  .catch(function (error) {
    // handle error`
    console.log(error);
  })
  .finally(function () {
    // always executed
    isInProgress.value = false;
  });
}

</script>

<template>
  <main>
    <h1>Configuration for Esp32</h1>
    <p style="color:green" v-show="isDataUpdated?'display':''">Config is updated. You should reboot esp.</p>
    <form>
        <div class="form-group mb-2">
    <label for="hotspotname">Hotspot Name</label>
    <input v-model="data.cfg.hotspot.name" type="email" class="form-control form-control-lg" id="hotspotname" aria-describedby="hotspotnameHelp" placeholder="Enter hotspot name">
    <small id="hotspotnameHelp" class="form-text text-muted">Hotspot name for AP.</small>
  </div>
        <div class="form-group mb-2">
  <label for="hotspotip">Hotspot IP</label>
  <input v-model="data.cfg.hotspot.ip" type="text" class="form-control form-control-lg" id="hotspotip" aria-describedby="hotspotipHelp" placeholder="Enter hotspot IP">
  <small id="hotspotipHelp" class="form-text text-muted">IP address for hotspot.</small>
</div>
<div class="form-group mb-2">
  <label for="hotspotmask">Hotspot Mask</label>
  <input v-model="data.cfg.hotspot.mask"  type="text" class="form-control form-control-lg" id="hotspotmask" aria-describedby="hotspotmaskHelp" placeholder="Enter hotspot mask">
  <small id="hotspotmaskHelp" class="form-text text-muted">Mask for hotspot.</small>
</div>
<div class="form-group mb-2">
  <label for="hotspotlogin">Hotspot Login</label>
  <input  v-model="data.cfg.hotspot.login" type="text" class="form-control form-control-lg" id="hotspotlogin" aria-describedby="hotspotloginHelp" placeholder="Enter hotspot login">
  <small id="hotspotloginHelp" class="form-text text-muted">Login for hotspot.</small>
</div>
<div class="form-group mb-2">
  <label for="hotspotpassword">Hotspot Password</label>
  <input v-model="data.cfg.hotspot.password"  type="password" class="form-control form-control-lg" id="hotspotpassword" aria-describedby="hotspotpasswordHelp" placeholder="Enter hotspot password">
  <small id="hotspotpasswordHelp" class="form-text text-muted">Password for hotspot.</small>
</div>
<div class="form-group mb-2">
  <label for="wifissid">WiFi SSID</label>
  <input  v-model="data.cfg.wifi.ssid" type="text" class="form-control form-control-lg" id="wifissid" aria-describedby="wifissidHelp" placeholder="Enter WiFi SSID">
  <small id="wifissidHelp" class="form-text text-muted">SSID for WiFi connection.</small>
</div>
<div class="form-group mb-2">
  <label for="wifipassword">WiFi Password</label>
  <input v-model="data.cfg.wifi.password"  type="password" class="form-control form-control-lg" id="wifipassword" aria-describedby="wifipasswordHelp" placeholder="Enter WiFi password">
  <small id="wifipasswordHelp" class="form-text text-muted">Password for WiFi connection.</small>
</div>
<div class="form-group mb-2">
  <label for="mqttserverpath">MQTT Server Path</label>
  <input v-model="data.cfg.mqtt.serverPath" type="text" class="form-control form-control-lg" id="mqttserverpath" aria-describedby="mqttserverpathHelp" placeholder="Enter MQTT server path">
  <small id="mqttserverpathHelp" class="form-text text-muted">Path for MQTT server.</small>
</div>
<div class="form-group mb-2">
  <label for="mqttusername">MQTT Username</label>
  <input v-model="data.cfg.mqtt.username" type="text" class="form-control form-control-lg" id="mqttusername" aria-describedby="mqttusernameHelp" placeholder="Enter MQTT username">
  <small id="mqttusernameHelp" class="form-text text-muted">Username for MQTT connection.</small>
</div>
<div class="form-group mb-2">
  <label for="mqttpassword">MQTT Password</label>
  <input v-model="data.cfg.mqtt.password" type="password" class="form-control form-control-lg" id="mqttpassword" aria-describedby="mqttpasswordHelp" placeholder="Enter MQTT password">
  <small id="mqttpasswordHelp" class="form-text text-muted">Password for MQTT connection.</small>
</div>
<div class="form-group mb-7">
  <label for="mqttport">MQTT Port</label>
  <input v-model="data.cfg.mqtt.port" type="number" class="form-control form-control-lg" id="mqttport" aria-describedby="mqttportHelp" placeholder="Enter MQTT port">
  <small id="mqttportHelp" class="form-text text-muted">Port for MQTT connection.</small>
</div>

<div class="form-group mb-2">
  <label for="temperaturetopic">Temperature Topic</label>
  <input v-model="data.cfg.floorControl.temperatureTopic" type="text" class="form-control form-control-lg" id="temperaturetopic" aria-describedby="temperaturetopicHelp" placeholder="Enter Temperature topic">
  <small id="temperaturetopicHelp" class="form-text text-muted">Mqtt temperature topic</small>
</div>
<div class="form-group mb-2">
  <label for="taptopic">Tap Topic</label>
  <input v-model="data.cfg.floorControl.tapTopic" type="text" class="form-control form-control-lg" id="taptopic" aria-describedby="taptopicHelp" placeholder="Enter Tap topic">
  <small id="taptopicHelp" class="form-text text-muted">Mqtt tap topic</small>
</div>

<div class="form-group mb-2">
  <label for="mintemperature">min temperature</label>
  <input v-model="data.cfg.floorControl.minTemperature" type="number" class="form-control form-control-lg" id="mintemperature" aria-describedby="mintemperatureHelp" placeholder="Enter min temperature">
  <small id="mintemperatureHelp" class="form-text text-muted">min temperature</small>
</div>


<div class="form-group mb-2">
  <label for="maxtemperature">max temperature</label>
  <input v-model="data.cfg.floorControl.maxTemperature" type="number" class="form-control form-control-lg" id="maxtemperature" aria-describedby="maxtemperatureHelp" placeholder="Enter max temperature">
  <small id="maxtemperatureHelp" class="form-text text-muted">max temperature</small>
</div>

  <button type="button" class="btn btn-primary mb-5" @click="saveConfig" :disabled="isInProgress">Save</button>
</form>
  </main>
</template>
