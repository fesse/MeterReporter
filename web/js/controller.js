
var consumptionGauge;
var productionGague;

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
	};

	var target = document.getElementById('ConsumptionGauge'); // your canvas element
	consumptionGauge = new Gauge(target).setOptions(opts); // create sexy gauge!
	consumptionGauge.maxValue = 20000; // set max gauge value
	consumptionGauge.setMinValue(0);  // Prefer setter over gauge.minValue = 0
	consumptionGauge.animationSpeed = 32; // set animation speed (32 is default value)
	consumptionGauge.set(0);

	target = document.getElementById('ProductionGauge'); // your canvas element
	productionGague = new Gauge(target).setOptions(opts); // create sexy gauge!
	productionGague.maxValue = 14000; // set max gauge value
	productionGague.setMinValue(0);  // Prefer setter over gauge.minValue = 0
	productionGague.animationSpeed = 32; // set animation speed (32 is default value)
	productionGague.set(0);

	setInterval(function () {
		updateGuages();
	}, 4000);
}

function updateGuages() {
	var value = meterInterface.getConsumption();
	document.getElementById("ConsumptionValue").innerHTML = value;
	consumptionGauge.set(value);

	value = meterInterface.getProduction();
	document.getElementById("ProductionValue").innerHTML = value;
	productionGague.set(value);
}

init();
