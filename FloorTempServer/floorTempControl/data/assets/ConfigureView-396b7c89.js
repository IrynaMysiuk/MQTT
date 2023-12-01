import{d as u,r as d,b as m,e as h,o as g,c as _,w as l,v as b,u as e,a as t,f as a}from"./index-e3fd19ff.js";import{a as c}from"./axios-28bc18a3.js";const x=t("h1",null,"Configuration for Esp32",-1),w={style:{color:"green"}},T={class:"form-group mb-2"},v=t("label",{for:"hotspotname"},"Hotspot Name",-1),y=t("small",{id:"hotspotnameHelp",class:"form-text text-muted"},"Hotspot name for AP.",-1),H={class:"form-group mb-2"},q=t("label",{for:"hotspotip"},"Hotspot IP",-1),M=t("small",{id:"hotspotipHelp",class:"form-text text-muted"},"IP address for hotspot.",-1),P={class:"form-group mb-2"},U=t("label",{for:"hotspotmask"},"Hotspot Mask",-1),E=t("small",{id:"hotspotmaskHelp",class:"form-text text-muted"},"Mask for hotspot.",-1),V={class:"form-group mb-2"},C=t("label",{for:"hotspotlogin"},"Hotspot Login",-1),k=t("small",{id:"hotspotloginHelp",class:"form-text text-muted"},"Login for hotspot.",-1),Q={class:"form-group mb-2"},S=t("label",{for:"hotspotpassword"},"Hotspot Password",-1),I=t("small",{id:"hotspotpasswordHelp",class:"form-text text-muted"},"Password for hotspot.",-1),F={class:"form-group mb-2"},W=t("label",{for:"wifissid"},"WiFi SSID",-1),D=t("small",{id:"wifissidHelp",class:"form-text text-muted"},"SSID for WiFi connection.",-1),B={class:"form-group mb-2"},L=t("label",{for:"wifipassword"},"WiFi Password",-1),N=t("small",{id:"wifipasswordHelp",class:"form-text text-muted"},"Password for WiFi connection.",-1),A={class:"form-group mb-2"},Y=t("label",{for:"mqttserverpath"},"MQTT Server Path",-1),j=t("small",{id:"mqttserverpathHelp",class:"form-text text-muted"},"Path for MQTT server.",-1),z={class:"form-group mb-2"},G=t("label",{for:"mqttusername"},"MQTT Username",-1),J=t("small",{id:"mqttusernameHelp",class:"form-text text-muted"},"Username for MQTT connection.",-1),K={class:"form-group mb-2"},O=t("label",{for:"mqttpassword"},"MQTT Password",-1),R=t("small",{id:"mqttpasswordHelp",class:"form-text text-muted"},"Password for MQTT connection.",-1),X={class:"form-group mb-7"},Z=t("label",{for:"mqttport"},"MQTT Port",-1),$=t("small",{id:"mqttportHelp",class:"form-text text-muted"},"Port for MQTT connection.",-1),tt={class:"form-group mb-2"},ot=t("label",{for:"temperaturetopic"},"Temperature Topic",-1),et=t("small",{id:"temperaturetopicHelp",class:"form-text text-muted"},"Mqtt temperature topic",-1),st={class:"form-group mb-2"},rt=t("label",{for:"taptopic"},"Tap Topic",-1),lt=t("small",{id:"taptopicHelp",class:"form-text text-muted"},"Mqtt tap topic",-1),at={class:"form-group mb-2"},pt=t("label",{for:"mintemperature"},"min temperature",-1),it=t("small",{id:"mintemperatureHelp",class:"form-text text-muted"},"min temperature",-1),nt={class:"form-group mb-2"},dt=t("label",{for:"maxtemperature"},"max temperature",-1),mt=t("small",{id:"maxtemperatureHelp",class:"form-text text-muted"},"max temperature",-1),ct=["disabled"],gt=u({__name:"ConfigureView",setup(ft){var o=d({cfg:{hotspot:{name:"",ip:"",mask:"",login:"",password:""},wifi:{ssid:"",password:""},mqtt:{serverPath:"",username:"",password:"",port:0},floorControl:{temperatureTopic:"",tapTopic:"",minTemperature:20,maxTemperature:30}}}),i=m(!1),n=m(!1);h(()=>{i.value=!0,c.get("/api/config").then(function(p){console.log(p),o.cfg=d(p.data)}).catch(function(p){console.log(p)}).finally(function(){i.value=!1})});function f(){i.value=!0,c({method:"post",url:"/api/config/save",data:o.cfg}).then(function(p){console.log(p),n.value=!0}).catch(function(p){console.log(p)}).finally(function(){i.value=!1})}return(p,s)=>(g(),_("main",null,[x,l(t("p",w,"Config is updated. You should reboot esp.",512),[[b,e(n)?"display":""]]),t("form",null,[t("div",T,[v,l(t("input",{"onUpdate:modelValue":s[0]||(s[0]=r=>e(o).cfg.hotspot.name=r),type:"email",class:"form-control form-control-lg",id:"hotspotname","aria-describedby":"hotspotnameHelp",placeholder:"Enter hotspot name"},null,512),[[a,e(o).cfg.hotspot.name]]),y]),t("div",H,[q,l(t("input",{"onUpdate:modelValue":s[1]||(s[1]=r=>e(o).cfg.hotspot.ip=r),type:"text",class:"form-control form-control-lg",id:"hotspotip","aria-describedby":"hotspotipHelp",placeholder:"Enter hotspot IP"},null,512),[[a,e(o).cfg.hotspot.ip]]),M]),t("div",P,[U,l(t("input",{"onUpdate:modelValue":s[2]||(s[2]=r=>e(o).cfg.hotspot.mask=r),type:"text",class:"form-control form-control-lg",id:"hotspotmask","aria-describedby":"hotspotmaskHelp",placeholder:"Enter hotspot mask"},null,512),[[a,e(o).cfg.hotspot.mask]]),E]),t("div",V,[C,l(t("input",{"onUpdate:modelValue":s[3]||(s[3]=r=>e(o).cfg.hotspot.login=r),type:"text",class:"form-control form-control-lg",id:"hotspotlogin","aria-describedby":"hotspotloginHelp",placeholder:"Enter hotspot login"},null,512),[[a,e(o).cfg.hotspot.login]]),k]),t("div",Q,[S,l(t("input",{"onUpdate:modelValue":s[4]||(s[4]=r=>e(o).cfg.hotspot.password=r),type:"password",class:"form-control form-control-lg",id:"hotspotpassword","aria-describedby":"hotspotpasswordHelp",placeholder:"Enter hotspot password"},null,512),[[a,e(o).cfg.hotspot.password]]),I]),t("div",F,[W,l(t("input",{"onUpdate:modelValue":s[5]||(s[5]=r=>e(o).cfg.wifi.ssid=r),type:"text",class:"form-control form-control-lg",id:"wifissid","aria-describedby":"wifissidHelp",placeholder:"Enter WiFi SSID"},null,512),[[a,e(o).cfg.wifi.ssid]]),D]),t("div",B,[L,l(t("input",{"onUpdate:modelValue":s[6]||(s[6]=r=>e(o).cfg.wifi.password=r),type:"password",class:"form-control form-control-lg",id:"wifipassword","aria-describedby":"wifipasswordHelp",placeholder:"Enter WiFi password"},null,512),[[a,e(o).cfg.wifi.password]]),N]),t("div",A,[Y,l(t("input",{"onUpdate:modelValue":s[7]||(s[7]=r=>e(o).cfg.mqtt.serverPath=r),type:"text",class:"form-control form-control-lg",id:"mqttserverpath","aria-describedby":"mqttserverpathHelp",placeholder:"Enter MQTT server path"},null,512),[[a,e(o).cfg.mqtt.serverPath]]),j]),t("div",z,[G,l(t("input",{"onUpdate:modelValue":s[8]||(s[8]=r=>e(o).cfg.mqtt.username=r),type:"text",class:"form-control form-control-lg",id:"mqttusername","aria-describedby":"mqttusernameHelp",placeholder:"Enter MQTT username"},null,512),[[a,e(o).cfg.mqtt.username]]),J]),t("div",K,[O,l(t("input",{"onUpdate:modelValue":s[9]||(s[9]=r=>e(o).cfg.mqtt.password=r),type:"password",class:"form-control form-control-lg",id:"mqttpassword","aria-describedby":"mqttpasswordHelp",placeholder:"Enter MQTT password"},null,512),[[a,e(o).cfg.mqtt.password]]),R]),t("div",X,[Z,l(t("input",{"onUpdate:modelValue":s[10]||(s[10]=r=>e(o).cfg.mqtt.port=r),type:"number",class:"form-control form-control-lg",id:"mqttport","aria-describedby":"mqttportHelp",placeholder:"Enter MQTT port"},null,512),[[a,e(o).cfg.mqtt.port]]),$]),t("div",tt,[ot,l(t("input",{"onUpdate:modelValue":s[11]||(s[11]=r=>e(o).cfg.floorControl.temperatureTopic=r),type:"text",class:"form-control form-control-lg",id:"temperaturetopic","aria-describedby":"temperaturetopicHelp",placeholder:"Enter Temperature topic"},null,512),[[a,e(o).cfg.floorControl.temperatureTopic]]),et]),t("div",st,[rt,l(t("input",{"onUpdate:modelValue":s[12]||(s[12]=r=>e(o).cfg.floorControl.tapTopic=r),type:"text",class:"form-control form-control-lg",id:"taptopic","aria-describedby":"taptopicHelp",placeholder:"Enter Tap topic"},null,512),[[a,e(o).cfg.floorControl.tapTopic]]),lt]),t("div",at,[pt,l(t("input",{"onUpdate:modelValue":s[13]||(s[13]=r=>e(o).cfg.floorControl.minTemperature=r),type:"number",class:"form-control form-control-lg",id:"mintemperature","aria-describedby":"mintemperatureHelp",placeholder:"Enter min temperature"},null,512),[[a,e(o).cfg.floorControl.minTemperature]]),it]),t("div",nt,[dt,l(t("input",{"onUpdate:modelValue":s[14]||(s[14]=r=>e(o).cfg.floorControl.maxTemperature=r),type:"number",class:"form-control form-control-lg",id:"maxtemperature","aria-describedby":"maxtemperatureHelp",placeholder:"Enter max temperature"},null,512),[[a,e(o).cfg.floorControl.maxTemperature]]),mt]),t("button",{type:"button",class:"btn btn-primary mb-5",onClick:f,disabled:e(i)},"Save",8,ct)])]))}});export{gt as default};
