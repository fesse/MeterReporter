meterInterface = function () {

	const ACTIVE_EFFECT_CONSUMPTION = "1-0:1.7.0";
	const ACTIVE_EFFECT_PRODUCTION = "1-0:2.7.0";

	var data = "";

	function fetchData() {
		console.log("FETCH DATA");
		var xhttp = new XMLHttpRequest();
		xhttp.onreadystatechange = function () {
			if (this.readyState == 4 && this.status == 200) {
				data = this.responseText;
			}
		};
		xhttp.open("GET", "http://192.168.1.202/status", true);
		xhttp.send();
	}

	function initFetchTimer() {
		setInterval(function () {
			fetchData();
		}, 10000);
	}

	function init(deviceId, tokenId) {
		fetchData();
		initFetchTimer();
	}

	function getSpecificValue(dataPoint) {
		var dataString = data.split('\r').filter(line => line.startsWith(dataPoint))[0];
		dataString = dataString.substring(dataString.indexOf("(") + 1);
		dataString = dataString.substring(0, dataString.indexOf("*"));
		return parseFloat(dataString) * 1000;
	}

	function getConsumption() {
		return getSpecificValue(ACTIVE_EFFECT_CONSUMPTION);
	}

	function getProduction() {
		return getSpecificValue(ACTIVE_EFFECT_PRODUCTION);
	}

	init();

	return {
		getConsumption: getConsumption,
		getProduction: getProduction
	};
}();