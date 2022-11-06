meterInterface = function () {

	const TIME = "0-0:1.0.0";
	const ACTIVE_EFFECT_CONSUMPTION = "1-0:1.7.0";
	const ACTIVE_EFFECT_PRODUCTION = "1-0:2.7.0";

	var data = "";
	var prevData = "";

	function fetchData() {
		var xhttp = new XMLHttpRequest();
		xhttp.onreadystatechange = function () {
			if (this.readyState == 4 && this.status == 200) {
				data = this.responseText;
			}
		};
		xhttp.open("GET", "http://192.168.1.202/status", true);
		xhttp.send();
	}

	/**
	 * Call each second. When the answer is new, fallback to
	 * 10 seconds to synch with the meter reporting period.
	 */
	calibrateFetchTimer = function () {
		if (prevData != data && prevData != "") {
			prevData = "";
			setInterval(function () {
				fetchData();
			}, 10000);
		} else {
			prevData = data;
			fetchData();
			setTimeout(calibrateFetchTimer, 1000);
		}
	}

	function init(deviceId, tokenId) {
		calibrateFetchTimer();
	}

	function getSpecificValue(dataPoint) {
		var dataString = data.split('\r').filter(line => line.startsWith(dataPoint))[0];
		dataString = dataString.substring(dataString.indexOf("(") + 1);
		dataString = dataString.substring(0, dataString.indexOf("*"));
		return Math.floor(parseFloat(dataString) * 1000);
	}

	function getConsumption() {
		return getSpecificValue(ACTIVE_EFFECT_CONSUMPTION);
	}

	function getProduction() {
		return getSpecificValue(ACTIVE_EFFECT_PRODUCTION);
	}

	function getTime() {
		var dataString = data.split('\r').filter(line => line.startsWith(TIME))[0];
		dataString = dataString.substring(dataString.indexOf("(") + 1);
		dataString = dataString.substring(0, dataString.indexOf("W"));
		return dataString.substring(0, 6) + " " + dataString.substring(6, 8) + ":" +
			dataString.substring(8, 10) + ":" + dataString.substring(10);
	}

	init();

	return {
		getConsumption: getConsumption,
		getProduction: getProduction,
		getTime: getTime
	};
}();