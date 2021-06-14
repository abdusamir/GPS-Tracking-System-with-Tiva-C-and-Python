import folium
import pandas as pd


data=pd.read_csv("locations.txt")

lat=data['Latitude'].tolist()
lon=data['Longitude'].tolist()
points =[]
avg_lat=sum(lat)/len(lat)
avg_log=sum(lon)/len(lon)
for i in range(len(lat)):
    points.append([lat[i],lon[i]])
my_map=folium.Map(location=[avg_lat,avg_log],zoom_start=50)

folium.PolyLine(points,color="green",opacity=1).add_to(my_map)

my_map.save("./map.html")
