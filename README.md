# GPS-Tracking-System-with-Tiva-C-and-Python

The idea of the project is to read the NMEA Values from Neo 6m GPS module using UART protocol and Tiva C
and then save the latitude and longitude values each second until the distance reaches 100 meters.

Then I save these values in a txt file to read them using python.

Afterwards I parse this data using python script to print the trajectory of the path taken using folium.
