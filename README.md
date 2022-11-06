# MeterReporter

A Particle project named MeterReporter
Read Serial1 at 115200 from the PowerMeter. Relay the result on a webpage.

For web page interface: http://192.168.1.202
For raw data: http://192.168.1.202/status

If changes are made inside the web folder, the generated resources needs to be
recreated by running ./CreateWebResources

Example raw data:
---------------------------------------
```
/LGF5E360

0-0:1.0.0(221105140250W)
1-0:1.8.0(00001071.363*kWh)
1-0:2.8.0(00000275.038*kWh)
1-0:3.8.0(00000182.031*kVArh)
1-0:4.8.0(00000042.767*kVArh)
1-0:1.7.0(0000.235*kW)
1-0:2.7.0(0000.000*kW)
1-0:3.7.0(0000.000*kVAr)
1-0:4.7.0(0000.222*kVAr)
1-0:21.7.0(0000.043*kW)
1-0:22.7.0(0000.000*kW)
1-0:41.7.0(0000.000*kW)
1-0:42.7.0(0000.101*kW)
1-0:61.7.0(0000.293*kW)
1-0:62.7.0(0000.000*kW)
1-0:23.7.0(0000.000*kVAr)
1-0:24.7.0(0000.025*kVAr)
1-0:43.7.0(0000.000*kVAr)
1-0:44.7.0(0000.170*kVAr)
1-0:63.7.0(0000.000*kVAr)
1-0:64.7.0(0000.026*kVAr)
1-0:32.7.0(229.3*V)
1-0:52.7.0(228.6*V)
1-0:72.7.0(231.3*V)
1-0:31.7.0(000.2*A)
1-0:51.7.0(000.8*A)
1-0:71.7.0(001.2*A)
!2132
```
---------------------------------------
