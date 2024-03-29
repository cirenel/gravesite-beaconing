import csv 
from geojson import Feature, FeatureCollection, Point #import via pip install geojson 
import json
import numpy

csvFilePath = 'nameNplotNcoord.csv'
features = []
with open(csvFilePath) as csvFile:
    csvReader = csv.DictReader(csvFile)
    for row in csvReader:
        if row['Lat'] != '':
            latitude = float(row['Lat'])
            longitude = float(row['Lon'])
            features.append(
                Feature(
                    geometry = Point((latitude, longitude)),
                    properties = {
                        'fname' : (row['fname']).strip(),
                        'lname' : (row['lname']).strip(),
                        'section' : (row['Section']).strip(),
                        'plot' : (row['Plot']).strip()
                    }
                )
            )
collection = FeatureCollection(features)
with open("graves.json", "w") as f:
    f.write('%s' % collection)