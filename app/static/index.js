function showTemperature(temperatureString) {
  show("temperature-element", temperatureString);
}

//function showVolume(volumeString) {
//  show("volume-element", volumeString);
//}

function showHumidity(humidityString) {
  show("humidity-element", humidityString);
}

function show(id, text) {
  const element = document.getElementById(id);

  const textContent = document.createTextNode(text);
  element.replaceChildren(textContent);
}

setInterval(async function () {
//    const url = `http://192.168.43.182:8080/api/v1/get_data/${id}`;
    const url = `http://127.0.0.1:8080/api/v1/get_data/${id}`
    const response = await fetch(url);
    const data = await response.json();
    temperature = await data["temperature"];
//    volume = await data["volume"]
    humidity = await data["humidity"]
    showTemperature(data["temperature"])
//    showVolume(data["volume"])
    showHumidity(data["humidity"])
}, 1000);
