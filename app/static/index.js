function showTemperature(temperatureString) {
  show("temperature-element1", temperatureString);
}

//function showVolume(volumeString) {
//  show("volume-element", volumeString);
//}

function showHumidity(humidityString) {
  show("humidity-element1", humidityString);
}


function show(id, text) {
  const element = document.getElementById(id);

  const textContent = document.createTextNode(text);
  element.replaceChildren(textContent);
}

setInterval(async function () {
//    const url = `http://192.168.43.182:8080/api/v1/get_data/${id}`;
    const url = `http://192.168.1.103:8080/api/v1/get_data/${hubId}/${sensorId}`
    const response = await fetch(url);
    const data = await response.json();

    temperature1 = await data["temperature"];
    humidity1 = await data["humidity"]
    showTemperature(temperature1)
    showHumidity(humidity1)
}, 1000);
