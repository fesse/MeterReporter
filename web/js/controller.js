
var gauge;

function init() {
	var opts = {
		angle: 0.15, // The span of the gauge arc
		lineWidth: 0.44, // The line thickness
		radiusScale: 1, // Relative radius
		pointer: {
			length: 0.6, // // Relative to gauge radius
			strokeWidth: 0.035, // The thickness
			color: '#000000' // Fill color
		},
		limitMax: false,     // If false, max value increases automatically if value > maxValue
		limitMin: false,     // If true, the min value of the gauge will be fixed
		colorStart: '#6FADCF',   // Colors
		colorStop: '#8FC0DA',    // just experiment with them
		strokeColor: '#E0E0E0',  // to see which ones work best for you
		generateGradient: true,
		highDpiSupport: true,     // High resolution support

		staticZones: [
			{ strokeStyle: "#F03E3E", min: 0, max: 15000 },
			{ strokeStyle: "#30B32D", min: 15000, max: 30000 }
		],
	};

	var target = document.getElementById('Gauge'); // your canvas element
	gauge = new Gauge(target).setOptions(opts); // create sexy gauge!
	gauge.maxValue = 30000; // set max gauge value
	gauge.setMinValue(0);  // Prefer setter over gauge.minValue = 0
	gauge.animationSpeed = 32; // set animation speed (32 is default value)
	gauge.set(15000);

	setInterval(function () {
		updateGuage();
	}, 1000);
}

function updateGuage() {
	var value = -meterInterface.getConsumption();
	value += meterInterface.getProduction();
	gauge.set(15000 + value);
	document.getElementById("Value").innerHTML = value + " W";
	document.getElementById("Time").innerHTML = meterInterface.getTime();
}

init();
