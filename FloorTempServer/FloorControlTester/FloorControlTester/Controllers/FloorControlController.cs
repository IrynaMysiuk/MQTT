using System.Text.Json;
using Microsoft.AspNetCore.Mvc;

namespace FloorControlTester.Controllers;


[ApiController]
[Route("config")]
public class FloorControlController : ControllerBase
{
    static FloorConfig cfg = new FloorConfig
    {
        Hotspot= new HotspotConfig
        {
            Name = "hotspot name",
            Ip = "12.12.21.12",
            Mask = "255.255.255.0",
            Login = "hp login",
            Password = "hp pass",
        },
        Wifi = new WifiConfig
        {
            Ssid = "wifissid",
            Password = "wifipass",
        },
        Mqtt = new MqttConfig
        {
            ServerPath = "mqtt serve",
            Password = "mqtt pass",
            Username = "mqtt username",
            Port = 445
        }
    };

    private readonly ILogger<WeatherForecastController> _logger;

    public FloorControlController(ILogger<WeatherForecastController> logger)
    {
        _logger = logger;
    }


    [HttpGet(Name = "GetConfig")]
    
    public JsonResult Get()
    {
        return new JsonResult(cfg);

    }

    [HttpPost]
    public ActionResult SaveConfig(FloorConfig config) {
        cfg = config;
        return Ok();
    }
}

